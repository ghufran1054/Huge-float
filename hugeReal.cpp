#include "hugeReal.h"

int hugeReal::base = 10;
hugeReal::hugeReal(int s, int p ) : Ds{ new int[s] {} }, size{ s }, pos{ p }, isNeg{ false }
{

}

hugeReal::hugeReal(const string& num)
{
	this->strToReal(num);
}
hugeReal::hugeReal(istream& rdr):isNeg{false}
{
	string num;
	rdr >> num;
	strToReal(num);
}
bool hugeReal::QwiseLess(const hugeReal& N2)const
{
	return N2.QwiseGreat(*this);
}
bool hugeReal::QwiseEqual(const hugeReal& N2)const
{
	if (this->size != N2.size)
		return false;
	for (int i = 0; i < this->size; i++)
	{
		if (Ds[i] != N2.Ds[i])
			return false;
	}
	return true;
}

bool hugeReal::operator>(const hugeReal& N2)const
{
	if (this->isNeg == N2.isNeg)
	{
		if (this->isNeg == false)
		{
			return QwiseGreat(N2);
		}
		else
		{
			return N2.QwiseGreat(*this);
		}
		
	}
	else
	{
		if (this->isNeg == false)
			return true;
		else
			return false;
	}
	
}
bool hugeReal::operator<(const hugeReal& N2)const
{
	return N2 > *this;
}
hugeReal hugeReal::operator+(const hugeReal& N2)const
{
	hugeReal R;
	if (this->isNeg == N2.isNeg)
	{
		if (this->QwiseGreat(N2))
		{
			R=this->QwiseAdd(N2);
			R.isNeg = this->isNeg;
		}
		else
		{
			R=N2.QwiseAdd(*this);
			R.isNeg = this->isNeg;
		}
	}
	else
	{
		if (this->QwiseGreat(N2))
		{
			R = this->QwiseSub(N2);
			R.isNeg = this->isNeg;
		}
		else
		{
			R = N2.QwiseSub(*this);
			R.isNeg = N2.isNeg;
		}
	}
	if (R.size == 1 && R.Ds[0] == 0)
		R.isNeg = false;
	return R;
}
bool hugeReal::operator>=(const hugeReal& N2)const
{
	return (*this > N2 || *this == N2);
}

bool hugeReal::operator<=(const hugeReal& N2)const
{
	return (*this < N2 || *this == N2);
}
hugeReal hugeReal::operator+=(const hugeReal& N2)
{
	return *this = *this + N2;
}

hugeReal hugeReal::operator-=(const hugeReal& N2)
{
	return *this = *this - N2;
}


bool hugeReal::operator!=(const hugeReal& N2)const
{
	return !(*this == N2);
}

void hugeReal::shiftLeft()
{
	pos--;
	if (pos == 0)
	{
		int* temp = new int[this->size + 1]{};
		for (int i = 0; i < this->size; i++)
			temp[i + 1] = Ds[i];
		delete[]Ds;
		Ds = temp;
		size++;
		pos++ ;
	}
}
hugeReal hugeReal::operator*(const hugeReal& N2)const
{
	hugeReal N2copy = N2,thisCopy=*this, unit("1"), zero("0"), finalAns("0");
	N2copy.isNeg = false, thisCopy.isNeg = false;

	while (N2copy != zero)
	{
		hugeReal count = unit, R=thisCopy;
		while (count + count <= N2copy)
		{
			R += R;
			count += count;
		}
		if (N2copy < unit)
		{
			unit.shiftLeft();
			thisCopy.shiftLeft();
		}
		else
		{
			N2copy -= count;
			finalAns += R;
		}
		
	}
	finalAns.isNeg = (isNeg == N2.isNeg || finalAns==zero ? false : true);
	return finalAns;
}

const hugeReal& hugeReal::operator*=(const hugeReal& N2)
{
	return *this = *this * N2;
}

hugeReal hugeReal::operator/(const hugeReal& N2)const
{
	if (N2 == 1) // creates an array of one size initialized with zero so  its actually comparing with zero
		throw "Division by Zero Not Possible";
	hugeReal N2copy = N2, thisCopy = *this, unit("1"), zero("0"),finalAns("0");
	N2copy.isNeg = false, thisCopy.isNeg = false;
	int sBitAfterDec = 0;

	while (thisCopy != zero)
	{
		hugeReal R = N2copy, count = unit;
		while (R + R <= thisCopy)
		{
			R += R;
			count += count;
		}
		if (thisCopy < N2copy)
		{
			if (!sBitAfterDec)
			{
				for (int i = finalAns.pos; i < finalAns.size; i++)
				{
					if (finalAns.Ds[i] != 0)
						sBitAfterDec = i;
				}
			}
			if (finalAns.size - sBitAfterDec > 16 && (finalAns.size - sBitAfterDec) > this->size && (finalAns.size - sBitAfterDec) > N2.size)
			{
				if (finalAns.Ds[finalAns.size - 1] >= hugeReal::base / 2)
				{
					finalAns += unit;
				}
				break;
			}
			unit.shiftLeft();
			N2copy.shiftLeft();
			
		}
		else
		{
			thisCopy -= R;
			finalAns += count;
			
		}
	}
	finalAns.isNeg = (isNeg == N2.isNeg || finalAns == zero ? false : true);
	return finalAns;
}
const hugeReal& hugeReal::operator/=(const hugeReal& N2)
{
	return *this = *this / N2;
}
hugeReal hugeReal::operator-()const
{
	hugeReal R = *this;
	R.isNeg = !R.isNeg;
	return R;
}
hugeReal& hugeReal::operator++()
{
	hugeReal U("1");
	*this = *this + U;
	return *this;

}
hugeReal& hugeReal::operator--()
{
	hugeReal U("1");
	*this = *this - U;
	return *this;
}
hugeReal hugeReal::operator++(int)
{
	hugeReal U("1");
	hugeReal R = *this;
	*this += U;
	return R;
}
hugeReal hugeReal::operator--(int)
{
	hugeReal R = *this,U("1");
	*this -= U;
	return R;
}
hugeReal hugeReal:: operator-(const hugeReal& N2)const
{
	hugeReal N = -N2;
	return *this + N;
}
bool hugeReal::operator==(const hugeReal & N2)const
{
	return (isNeg == N2.isNeg && QwiseEqual(N2));
}
void hugeReal::shrink()
{
	int i = 0, s = this->size;
	for (i = this->size - 1; i >= pos; i--)
	{
		if (Ds[i] != 0)
			break;
		this->size--;
	}
	for (i = 0; i < pos-1; i++)
	{
		if (Ds[i] != 0)
			break;
	}
	if (s == this->size && i == 0)
		return;
	int* temp = new int[this->size-i];
	pos = pos - i;
	s = this->size - i;
	for (int k=0; i < this->size; i++,k++)
	{
		temp[k] = Ds[i];
	}
	this->size = s;
	delete[]Ds;
	Ds = temp;
}
void hugeReal::deepCopy(const hugeReal& R)
{
	this->size = R.size;
	this->pos = R.pos;
	this->isNeg = R.isNeg;
	this->base = R.base;
	this->Ds = new int[this->size];
	for (int i = 0; i < this->size; i++)
	{
		Ds[i] = R.Ds[i];
	}
}
hugeReal::hugeReal(const hugeReal& N)
{
	this->deepCopy(N);
}
const hugeReal& hugeReal::operator=(const hugeReal& N)
{
	if (this != &N)
	{
		delete[]this->Ds;
		this->deepCopy(N);
	}
	return *this;
}

int hugeReal::operator()(int i, int ind)const
{
	// i=0 means before the decimal and ind means how many digits before or after the decimal.
	if (i == 0)
	{
		if (ind < pos)
			return this->Ds[pos - 1 - ind];
		else
			return 0;
	}
	else
	{
		if (ind < size-pos)
			return this->Ds[pos + ind];
		else
			return 0;
	}
}
int& hugeReal::operator()(int i, int ind)
{
	if (i == 0)
	{
		return this->Ds[pos - 1 - ind];
	}
	else
	{
		return this->Ds[pos + ind];
	}
}
hugeReal hugeReal::QwiseAdd(const hugeReal& N2)const
{
	int MDAD = max(size - pos, N2.size - N2.pos);
	hugeReal R(this->pos + 1+ MDAD, this->pos + 1);

	int carry = 0;
	for (int i = MDAD - 1; i >= 0; i--)
	{
		int s = (*this)(1, i) + N2(1, i) + carry;
		R(1, i) = s % base;
		carry = s / base;

	}
	for (int i = 0; i < R.pos; i++)
	{
		int s = (*this)(0, i) + N2(0, i) + carry;
		R(0, i) = s % base;
		carry = s / base;
	}
	R.shrink();
	return R;
}

hugeReal hugeReal::QwiseSub(const hugeReal& N2)const
{
	int MDAD = max(size - pos, N2.size - N2.pos);
	hugeReal R(this->pos + MDAD, this->pos);

	int carry = 0;
	for (int i = MDAD - 1; i >= 0; i--)
	{
		int dif = (*this)(1, i) - N2(1, i) + carry;
		R(1, i) = (dif < 0 ? dif + base : dif);
		carry = (dif < 0 ? -1 : 0);
	}
	for (int i = 0; i < R.pos; i++)
	{
		int dif = (*this)(0, i) - N2(0, i) + carry;
		R(0, i) = (dif < 0 ? dif + base : dif);
		carry = (dif < 0 ? -1 : 0);
	}
	R.shrink();
	return R;
}

bool hugeReal::QwiseGreat(const hugeReal& N2)const
{
	if (this->pos > N2.pos)
		return true;
	else if (this->pos < N2.pos)
		return false;

	

	for (int i = 0; i < size && i < N2.size; i++)
	{
		if (Ds[i] > N2.Ds[i])
			return true;
		else if (Ds[i] < N2.Ds[i])
			return false;
	}

	if (this->size < N2.size)
		return false;

	else if (this->size > N2.size)
		return true;

	return false;
}
void hugeReal::strToReal(const string& num)
{
	int si = 0, di = 0;
	if (num[0] == '+')
	{
		si++;
		isNeg = false;
	}
	else if (num[0] == '-')
	{
		si++;
		isNeg = true;
	}
	this->size = num.size() - si;
	this->pos = this->size;
	for (int i = 0; i < num.size(); i++)
	{
		if (num[i] == '.')
		{
			pos = i - si;
			break;
		}
	}
	if (pos != 0)
	{
		if (pos != this->size)
			this->size--;
	}
	else
	{
		di++;
		pos++;
	}
	Ds = new int[this->size]{};
	for (int i = di; si < num.size() && i < this->size; si++)
	{
		if (num[si] == '.')
		{
			continue;
		}
		if (isalpha(num[si]))
			Ds[i] = toupper(num[si]) - 55;
		else
			Ds[i] = num[si] - char('0');
		if (Ds[i] >= hugeReal::base|| Ds[i]<0)
			throw"invalid digit in number";
		i++;
	}
	this->shrink();
}

istream& operator>>(istream& in, hugeReal& R)
{
	string num;
	in >> num;
	R.strToReal(num);
	return in;
}

ostream& operator<<(ostream& out, const hugeReal& R)
{
	if (R.isNeg)
		out << '-';
	for (int i = 0; i < R.size; i++)
	{
		if (i == R.pos)
			out << ".";

		if (R.Ds[i] > 9)
			out << char(R.Ds[i] + 55);
		else
			out<<R.Ds[i];
	}
	return out;
}