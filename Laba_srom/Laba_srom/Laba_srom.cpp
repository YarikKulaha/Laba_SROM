#include <iostream>
#include<string>
#include <cmath>

using namespace std;

class SROM
{

public:
	string str;
	unsigned long long lgth = 0;
	unsigned long long arr[72] = { 0 };
	int bin[2048] = { 0 };
	int deg = 0;
	int m_deg = 0;
	int deg_bit = 0;
};

SROM read(SROM A){
	unsigned long long B = 0;
	int j = 0;
	A.lgth = 0;
	int i = (A.str.length() - 1);
	while (i >= 0){
		if (A.str.length() > 8){
			while (j != 8){
				if (A.str[i] >= '0'){
					if (A.str[i] <= '9') {
						B = A.str[i] - 48;
					}
				}
				if (A.str[i] >= 65) {
					if (A.str[i] <= 70) {
						B = A.str[i] - 55;
					}
				}
				A.arr[A.lgth] = A.arr[A.lgth] + (B)*pow(16, (((A.str.length() - 1) - i) % 8));
				i--;
				j++;
			}
			j = 1;
			if ((i >= 0) && (A.str[i] >= '0') && (A.str[i] <= '9')){
					B = A.str[i] - 48;
					A.lgth++;
					A.arr[A.lgth] = A.arr[A.lgth] + (B)*pow(16, (((A.str.length() - 1) - i) % 8));
			}
			if ((i >= 0) && (A.str[i] >= 65) && (A.str[i] <= 70)){
					B = A.str[i] - 55;
					A.lgth++;
					A.arr[A.lgth] = A.arr[A.lgth] + (B)*pow(16, (((A.str.length() - 1) - i) % 8));
			}
		}
		if ((A.str.length() <= 8) && (A.str[i] >= '0') && (A.str[i] <= '9')){
			B = A.str[i] - 48;
			A.arr[0] = A.arr[0] + (B)*pow(16, ((A.str.length() - 1) - i) % 8);
		}
		if ((A.str.length() <= 8) && (A.str[i] >= 65) && (A.str[i] <= 70)){
			B = A.str[i] - 55;
			A.arr[0] = A.arr[0] + (B)*pow(16, ((A.str.length() - 1) - i) % 8);
		}
		i--;
	}
	A.lgth++;
	if ((A.arr[A.lgth - 1] == 0)) {
		if ((A.lgth != 1)) {
			while (A.lgth != 1){
				A.lgth--;
			}
		}
	}
	return A;
}

string record(SROM A){
	int B = 0, i = 0;
	char C = ' ';
	A.str = "";
	if (A.lgth == -1)
	{
		A.str = "Negative number.";
		return A.str;
	}
	if (i == 0) {
		while (i < A.lgth) {
			for (int j = 7; j >= 0; j--) {
				B = (A.arr[i]) % 16;
				if (B >= 0) {
					if (B <= 9) {
						C = B + 48;
						A.str = C + A.str;
						A.arr[i] = A.arr[i] / 16;
					}
				}
				if (B >= 10) {
					if (B <= 15) {
						C = B + 55;
						A.str = C + A.str;
						A.arr[i] = A.arr[i] / 16;
					}
				}
			}
			i++;
		}
	}
	int j = 0;
	while ((A.str[j] == '0') && (j < A.str.length() - 1)){
		A.str.erase(j, 1);
		j++;
	}
	return A.str;
}

int Check(SROM A, string B, int C){
	if (A.str != B)
	{
		return C;
	}
	else
	{
		C = 1;
		return C;
	}

}

SROM add(SROM A, SROM B, SROM C){
	unsigned long long D = 0, E = 0;
	long long carry = 0;
	int lgth = 0, i = 0;
	unsigned long long base = pow(16, 8);
	*C.arr = { 0 };
	C.lgth = 0;
	if (A.lgth == B.lgth) {
		lgth = A.lgth;
	}
	if (A.lgth > B.lgth){
		lgth = A.lgth;
	}
	if (A.lgth < B.lgth) {
		lgth = B.lgth;

	}
	while (i < lgth){
		D = A.arr[i] + B.arr[i];
		D = D + carry;
		C.arr[i] = (D) & (base - 1);
		carry = (D >> 32);
		i++;
	}
	C.lgth = lgth;
	if ((carry == 1)&&(C.lgth = lgth)){
		C.arr[lgth] = carry;
		C.lgth = lgth + 1;
	}
	return C;
}

int comp(SROM A, SROM B, int ans){
	ans = 0;
	if (A.lgth == B.lgth)
	{
		int i;
		i = (A.lgth - 1);
		while ((A.arr[i] == B.arr[i]) && (i > 0))
		{
			i = i - 1;
		}
		if (A.arr[i] > B.arr[i])
		{
			ans = 1;
			return ans;
		}
		if (A.arr[i] < B.arr[i])
		{
			ans = -1;
			return ans;
		}
	}
	else {
		if (A.lgth > B.lgth) {
			ans = 1;
		}
		if (A.lgth < B.lgth)
		{
			ans = -1;
		}
	}
	return ans;
}

SROM sub(SROM A, SROM B, SROM C, int D){
	long long E = 0, borrow = 0;
	int k = 0;
	C.lgth = 0;
	long long help = pow(16, 8);
	while ( k < C.lgth)
	{
		C.arr[k] = 0;
		k++;
	}
	if (D == 1){
		for (int i = 0; i < A.lgth; i++){
			E = A.arr[i] - B.arr[i];
			E = E - borrow;
			if (E == 0){
				C.arr[i] = E;
				C.lgth = C.lgth + 1;
				borrow = 0;
			}
			if (E > 0){
				C.arr[i] = E;
				C.lgth = C.lgth + 1;
				borrow = 0;
			}
			if (E < 0){
				C.arr[i] = help + E;
				C.lgth = C.lgth + 1;
				borrow = 1;
			}
		}
		while ((C.arr[C.lgth - 1] == 0) && (C.lgth != 1))
		{
			C.lgth = C.lgth - 1;
		}
	}
	else {
		if (D == -1)
		{
			C.lgth = -1;
		}
		if (D == 0)
		{
			C.lgth = 1;
			*C.arr = { 0 };
		}
	}
	return C;

}

SROM mul_digit(SROM A, SROM B, unsigned long long C){
	int i = 0;
	unsigned long long carry = 0, D = 0;
	long long base = pow(16, 8);
	B.lgth = 0;
	*B.arr = { 0 };
	while ( i < A.lgth){
		D = A.arr[i] * C;
		D = D + carry;
		B.arr[i] = D % base;
		carry = D / base;
		B.lgth = B.lgth + 1;
		i++;
	}
	if (carry != 0){
		B.arr[B.lgth] = carry;
		B.lgth ++;
	}
	return B;
}

SROM dig_high(SROM A, int B){
	int k = A.lgth;
	if ((B != 0)&& (B == 1)){
		while(k > 0) {
			A.arr[k] = A.arr[k - 1];
			k--;
		}
		A.arr[0] = 0;
		A.lgth++;
	}
	if ((B != 0) && (B != 1)) {
		for (int i = 0; i < B; i++){
			for (int j = A.lgth; j > 0; j--)
			{
				A.arr[j] = A.arr[j - 1];
			}
			A.arr[i] = 0;
			A.lgth++;
		}
	}
	return A;
}

SROM mul(SROM A, SROM B, SROM C){
	int lgth = 0;
	int i = 0;
	SROM D, E;
	D.lgth = 0;
	E.lgth = 0;
	*C.arr = { 0 };
	C.lgth = 0;
	if (A.lgth > B.lgth){
		lgth = A.lgth;
	}
	if (A.lgth == B.lgth){
		lgth = A.lgth;
	}
	if (A.lgth < B.lgth) {
		lgth = B.lgth;
	}
	while (i < lgth){
		D = mul_digit(A, D, B.arr[i]);
		D = dig_high(D, i);
		C = add(C, D, E);
		i++;
	}
	return C;

}

SROM bin_num(SROM A){
	int c;
	A.lgth = 0;
	{
		for (int i = A.str.length() - 1; i >= 0; i--){
			if ((A.str[i] >= '0') && (A.str[i] <= '9'))
			{
				c = A.str[i] - 48;
			}
			if ((A.str[i] >= 65) && (A.str[i] <= 70))
			{
				c = A.str[i] - 55;
			}
			A.bin[A.lgth] = c % 2;
			A.lgth = A.lgth + 1;
			c = c / 2;
			A.bin[A.lgth] = c % 2;
			A.lgth = A.lgth + 1;
			c = c / 2;
			A.bin[A.lgth] = c % 2;
			A.lgth = A.lgth + 1;
			c = c / 2;
			A.bin[A.lgth] = c;
			A.lgth = A.lgth + 1;
		}
		while ((A.bin[(A.lgth) - 1] == 0) && (A.lgth > 1)){
			A.lgth = A.lgth - 1;
		}
	}
	return A;

}

SROM pow(SROM A, SROM B, SROM C)
{
	SROM Temp;
	if (B.bin[B.lgth - 1] == 0){
		C.lgth = 1;
		C.arr[0] = 1;
	}
	if (B.bin[B.lgth - 1] != 0) {
		C = A;
		for (int i = B.lgth - 2; i >= 0; i--){
			C = mul(C, C, Temp);
			if (B.bin[i] == 1)
			{
				C = mul(C, A, Temp);
			}
		}
	}
	while ((C.arr[C.lgth - 1] == 0) && (C.lgth > 1))
	{
		C.lgth = C.lgth - 1;
	}
	return C;
}

string bin_hex(SROM C)
{
	int temp = 0;
	char temp1 = ' ';
	C.str = "";
	if (C.lgth == -1){
		C.str = "Negative number.";
	}
	for (int i = 0; i < (C.lgth / 4) + 1; i++){
		temp = C.bin[4 * i] + C.bin[4 * i + 1] * 2 + C.bin[4 * i + 2] * 2 * 2 + C.bin[4 * i + 3] * 2 * 2 * 2;
		if ((temp >= 0) && (temp <= 9))
		{
			temp1 = temp + 48;
			C.str = temp1 + C.str;
		}
		if ((temp >= 10) && (temp <= 15))
		{
			temp1 = temp + 55;
			C.str = temp1 + C.str;
		}

	}
	int j = 0;
	while ((C.str[j] == '0') && (j < C.str.length() - 1))
	{
		C.str.erase(j, 1);
		j + 1;
	}

	return C.str;


}

SROM LongShiftBitsToHigh(SROM A, int shift)
{
	SROM Temp, Temp1;
	Temp = A;
	for (int i = 0; i < shift; i++)
	{
		Temp = mul_digit(Temp, Temp1, 2);
	}

	return Temp;
}

SROM SetTheBit(SROM A, int place)
{
	while (A.bin[place] == 1)
	{
		A.bin[place] = 0;
		place = place + 1;
	}
	A.bin[place] = 1;
	if (A.lgth <= place)
	{
		A.lgth = place + 1;
	}
	return A;
}

int BitLength(SROM A)
{
	int temp = 0;
	int answer = 0;
	temp = log2(A.arr[A.lgth - 1]) + 1;
	answer = temp + (A.lgth - 1) * 32;
	return answer;

}

void divis(SROM A, SROM B, SROM& R, SROM& Q)
{
	if (B.arr[B.lgth - 1] != 0)
	{
		SROM Temp, Temp1;
		int BitlengthB, BitlengthR;
		BitlengthB = BitLength(B);
		R = A;
		int FLAG = comp(R, B, 0);
		int FLAG1 = 0;
		while ((FLAG == 1) || (FLAG == 0))
		{
			BitlengthR = BitLength(R);
			Temp = LongShiftBitsToHigh(B, (BitlengthR - BitlengthB));
			FLAG1 = comp(R, Temp, 0);
			while ((FLAG1 == -1))
			{
				BitlengthR = BitlengthR - 1;
				Temp = LongShiftBitsToHigh(B, (BitlengthR - BitlengthB));
				FLAG1 = comp(R, Temp, 0);
			}
			Temp1 = sub(R, Temp, Temp1, FLAG1);
			R = Temp1;
			Q = SetTheBit(Q, (BitlengthR - BitlengthB));

			FLAG = comp(R, B, 0);
		}
	}
	else
	{
		cout << "!Divison on 0!" << endl;
		cout << endl;
	}

}

SROM LongDivisionOnTwo(SROM A)
{
	unsigned long long base = pow(16, 8);
	for (int i = 0; i < A.lgth; i++)
	{
		A.arr[i] = (A.arr[i] >> 1) + (A.arr[i + 1] << 31) & (base - 1);

	}
	while (A.arr[A.lgth - 1] == 0)
	{
		A.lgth = A.lgth - 1;
	}
	return A;
}

bool CheckEvenNumber(SROM A)
{
	if ((A.arr[0] & 1) == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

SROM gcd(SROM A, SROM B, SROM& D)
{
	D.arr[0] = 1;
	D.lgth = 1;
	SROM Temp, Temp1, Temp2;
	bool flagA, flagB;
	int ComRes = 0;
	flagA = CheckEvenNumber(A);
	flagB = CheckEvenNumber(B);
	while ((flagA == 1) && (flagB == 1))
	{
		A = LongDivisionOnTwo(A);
		B = LongDivisionOnTwo(B);
		D = mul_digit(D, Temp, 2);
		flagA = CheckEvenNumber(A);
		flagB = CheckEvenNumber(B);
	}
	while (flagA == 1)
	{
		A = LongDivisionOnTwo(A);
		flagA = CheckEvenNumber(A);

	}
	while (B.arr[B.lgth - 1] != 0)
	{
		while (flagB == 1)
		{
			B = LongDivisionOnTwo(B);
			flagB = CheckEvenNumber(B);
		}
		ComRes = comp(A, B, ComRes);
		if ((ComRes == 1) || (ComRes == 0))
		{
			Temp = A;
			A = B;
			flagA = flagB;
			B = sub(Temp, B, Temp1, ComRes);
			flagB = CheckEvenNumber(B);

		}
		else
		{
			B = sub(B, A, Temp1, 1);
			flagB = CheckEvenNumber(B);
		}

	}

	D = mul(A, D, Temp2);
	while (D.arr[D.lgth - 1] == 0)
	{
		D.lgth = D.lgth - 1;
	}

	return D;
}

SROM lcm(SROM A, SROM B, SROM GCD)
{
	SROM LCM;
	if ((GCD.lgth == 1) && (GCD.arr[0] == 1))
	{

		LCM = mul(A, B, LCM);
	}
	else
	{
		SROM R, Q, Temp;
		divis(A, GCD, R, Q);
		Q.str = bin_hex(Q);
		Q = read(Q);
		divis(B, GCD, Temp, R);
		R.str = bin_hex(R);
		R = read(R);
		Temp = mul(R, Q, Temp);
		LCM = mul(Temp, GCD, LCM);
	}
	return LCM;
}

SROM mod_add(SROM A, SROM B, SROM N){
	SROM Result, Temp, Q;
	int checkA = 0;
	int checkB = 0;
	checkA = comp(A, N, 0);
	checkB = comp(B, N, 0);
	if ((checkA == 0) && (checkB == 0))
	{
		Result.lgth = 1;
		return Result;

	}
	else
	{
		Temp = add(A, B, Temp);
		divis(Temp, N, Result, Q);
		return Result;

	}

}

SROM mod_sub(SROM A, SROM B, SROM N){
	int check, checkSub;;
	SROM Temp, Result, Q;
	check = comp(A, B, 0);
	if ((check == 1) || (check == 0))
	{

		Temp = sub(A, B, Temp, check);
		checkSub = comp(Temp, N, 0);
		if (checkSub == -1)
		{
			Result = Temp;
			return Result;
		}
		if (checkSub == 0)
		{
			Result.lgth = 1;
			return Result;
		}
		else
		{
			divis(Temp, N, Result, Q);
			return Result;
		}
	}
	else
	{
		SROM TempSub;
		Temp = sub(B, A, Temp, 1);
		checkSub = comp(Temp, N, 0);
		if (checkSub == -1)
		{
			Result = sub(N, Temp, Result, 1);
			return Result;
		}
		if (checkSub == 0)
		{
			Result.lgth = 1;
			return Result;
		}
		else
		{
			divis(Temp, N, TempSub, Q);
			Result = sub(N, TempSub, Result, 1);
			return Result;
		}
	}
}

SROM KillLastDigits(SROM A, int shift)
{
	SROM Temp;
	Temp.lgth = 0;
	for (int i = 0; i < (A.lgth - shift); i++)
	{
		Temp.arr[i] = A.arr[shift + i];
		Temp.lgth++;
	}

	while ((Temp.arr[Temp.lgth - 1] == 0) && (Temp.lgth > 1))
	{
		Temp.lgth = Temp.lgth - 1;
	}
	return Temp;
}

SROM LongDivisionModBase(SROM A, int BasePower, SROM& Temp)
{
	Temp.lgth = 0;
	for (int i = 0; i < BasePower; i++)
	{
		Temp.arr[i] = A.arr[i];
		Temp.lgth++;
	}
	while ((Temp.arr[Temp.lgth - 1] == 0) && (Temp.lgth > 1))
	{
		Temp.lgth = Temp.lgth - 1;
	}
	return Temp;
}

SROM bar_red(SROM X, SROM N, SROM M)
{
	SROM Q, Q2, Q3;
	SROM R, R1, R2, TempMul, TempSub;
	Q = KillLastDigits(X, (N.lgth - 1));
	Q2 = mul(Q, M, Q2);
	Q3 = KillLastDigits(Q2, (N.lgth + 1));
	R1 = LongDivisionModBase(X, (N.lgth + 1), R1);
	TempMul = mul(Q3, N, TempMul);
	R2 = LongDivisionModBase(TempMul, (N.lgth + 1), R2);
	int flag = comp(R1, R2, 0);
	R = sub(R1, R2, R, flag);
	int check = comp(R, N, 0);
	while ((check == 1) || (check == 0))
	{
		R = sub(R, N, TempSub, check);
		check = comp(R, N, 0);
	}

	return R;
}

SROM mod_pow_bar(SROM A, SROM B, SROM N, SROM M){
	SROM C;
	SROM TempMul, TempSquare;
	TempMul = A;
	TempMul.lgth = 2 * N.lgth;
	C = bar_red(TempMul, N, M);

	for (int i = B.lgth - 2; i >= 0; i--)
	{
		TempSquare = mul(C, C, TempSquare);
		if (TempSquare.lgth < (2 * N.lgth))
		{
			TempSquare.lgth = 2 * N.lgth;
		}
		C = bar_red(TempSquare, N, M);
		if (B.bin[i] == 1)
		{
			TempMul = mul(C, A, TempMul);
			if (TempMul.lgth < (2 * N.lgth))
			{
				TempMul.lgth = 2 * N.lgth;
			}
			C = bar_red(TempMul, N, M);

		}
	}
	return C;
}

SROM read3(SROM A) {
	int j = 0;
	unsigned long long B = 0;
	A.deg = 0;
	*A.arr = { 0 };
	for (int i = (A.str.length() - 1); i >= 0; i--) {
		if (A.str.length() > 8) {
			while ((j != 8) && (i != -1)) {
				if ((A.str[i] >= '0') && (A.str[i] <= '9')) {
					B = A.str[i] - 48;
				}
				if ((A.str[i] >= 65) && (A.str[i] <= 70)) {
					B = A.str[i] - 55;
				}
				A.arr[A.deg] = A.arr[A.deg] + (B)*pow(16, (((A.str.length() - 1) - i) % 8));
				i--;
				j++;
			}
			j = 1;
			if (i >= 0) {
				if ((A.str[i] >= '0') && (A.str[i] <= '9')) {
					B = A.str[i] - 48;
				}
				if ((A.str[i] >= 65) && (A.str[i] <= 70)) {
					B = A.str[i] - 55;
				}
				A.deg = A.deg + 1;
				A.arr[A.deg] = A.arr[A.deg] + (B)*pow(16, (((A.str.length() - 1) - i) % 8));
			}
		}
		if (A.str.length() <= 8) {
			if ((A.str[i] >= '0') && (A.str[i] <= '9')) {
				B = A.str[i] - 48;
			}
			if ((A.str[i] >= 65) && (A.str[i] <= 70)) {
				B = A.str[i] - 55;
			}
			A.arr[0] = A.arr[0] + (B)*pow(16, ((A.str.length() - 1) - i) % 8);
		}
	}
	A.deg++;
	while ((A.arr[A.deg - 1] == 0) && (A.deg != 1)) {
		A.deg--;
	}
	return A;
}

int max_deg3(SROM A) {
	int temp = 0, ans = 0;
	temp = log2(A.arr[A.deg - 1]) + 1;
	ans = temp + (A.deg - 1) * 32;
	return ans;
}

string record3(SROM A) {
	int B = 0;
	char C = ' ';
	A.str = "";
	for (int i = 0; i < A.deg; i++) {
		for (int j = 7; j >= 0; j--) {
			B = (A.arr[i]) % 16;
			if ((B >= 10) && (B <= 15)) {
				C = B + 55;
				A.str = C + A.str;
			}
			if ((B >= 0) && (B <= 9)) {
				C = B + 48;
				A.str = C + A.str;
			}
			A.arr[i] = A.arr[i] / 16;
		}
	}
	int j = 0;
	while ((A.str[j] == '0') && (j < A.str.length() - 1)) {
		A.str.erase(j, 1);
		j++;
	}
	return A.str;
}

SROM bin_num3(SROM A) {
	int B;
	A.m_deg = 0; {
		for (int i = A.str.length() - 1; i >= 0; i--) {
			if ((A.str[i] >= '0') && (A.str[i] <= '9')) {
				B = A.str[i] - 48;
			}
			if ((A.str[i] >= 65) && (A.str[i] <= 70)) {
				B = A.str[i] - 55;
			}
			A.bin[A.m_deg] = B % 2;
			A.m_deg = A.m_deg + 1;
			B = B / 2;
			A.bin[A.m_deg] = B % 2;
			A.m_deg = A.m_deg + 1;
			B = B / 2;
			A.bin[A.m_deg] = B % 2;
			A.m_deg = A.m_deg + 1;
			B = B / 2;
			A.bin[A.m_deg] = B;
			A.m_deg = A.m_deg + 1;
		}
		while ((A.bin[(A.m_deg) - 1] == 0) && (A.m_deg > 1)) {
			A.m_deg = A.m_deg - 1;
		}
	}
	return A;
}

string bin_hex3(SROM C) {
	int temp = 0, k = 4;
	char help = ' ';
	C.str = "";
	for (int i = 0; i < (C.m_deg / k) + 1; i++) {
		temp = C.bin[k * i] + C.bin[k * i + 1] * 2 + C.bin[k * i + 2] * k + C.bin[k * i + 3] * 8;
		if ((temp >= 0) && (temp <= 9)) {
			help = temp + 48;
			C.str = help + C.str;
		}
		if ((temp >= 10) && (temp <= 15)) {
			help = temp + 55;
			C.str = help + C.str;
		}
	}
	int j = 0;
	while ((C.str[j] == '0') && (j < C.str.length() - 1)) {
		C.str.erase(j, 1);
		j + 1;
	}
	return C.str;
}

SROM add3(SROM A, SROM B) {
	SROM C;
	if (A.deg < B.deg) {
		C.deg = B.deg;
	}
	if (A.deg >= B.deg) {
		C.deg = A.deg;
	}
	for (int i = 0; i < C.deg; i++) {
		C.arr[i] = A.arr[i] ^ B.arr[i];
	}
	while ((C.arr[C.deg - 1] == 0) && (C.deg > 1)) {
		C.deg = C.deg - 1;
	}
	return C;
}

SROM mul_1_dig3(SROM A, SROM B, int C) {
	unsigned long long temp = 0, carry = 0;
	long long base = pow(16, 8);
	B.deg = 0;
	*B.arr = { 0 };
	for (int i = 0; i < A.deg; i++) {
		temp = A.arr[i] * C + carry;
		B.arr[i] = temp % base;
		carry = temp / base;
		B.deg = B.deg + 1;
	}
	if (carry != 0) {
		B.arr[B.deg] = carry;
		B.deg = B.deg + 1;
	}
	return B;
}

SROM bit_high3(SROM A, int B) {
	SROM temp = A, help;
	for (int i = 0; i < B; i++) {
		temp = mul_1_dig3(temp, help, 2);
	}
	return temp;
}

int comp3(SROM A, SROM B, int C) {
	int A1, B1;
	C = 1;
	A1 = max_deg3(A);
	B1 = max_deg3(B);
	if (A1 < B1) {
		C = -1;
	}
	return C;
}

void mod_gen3(SROM A, SROM B, SROM& C) {
	if (B.arr[B.deg - 1] == 0) {
		cout << "ERROR" << endl;
	}
	if (B.arr[B.deg - 1] != 0) {
		SROM temp, help;
		int bit_B = max_deg3(B), bit_R;
		C = A;
		int help1 = comp3(C, B, 0), help2 = 0;
		while (help1 == 1) {
			bit_R = max_deg3(C);
			temp = bit_high3(B, (bit_R - bit_B));
			help2 = comp3(C, temp, 0);
			while ((help2 == -1))
			{
				bit_R = bit_R - 1;
				temp = bit_high3(B, (bit_R - bit_B));
				help2 = comp3(C, temp, 0);
			}
			help = add3(C, temp);
			C = help;
			help1 = comp3(C, B, 0);
		}
	}
}

int mask_bit3(SROM A, int B) {
	int C = pow(2, ((B) % 32)), D;
	D = (A.arr[B / 32] & C) >> ((B) % 32);
	return D;
}

SROM mult3(SROM A, SROM B) {
	int lgth = 0, bit_B = 0;
	SROM t_mul, C;
	t_mul = A;
	B.m_deg = max_deg3(B);
	for (int i = 0; i < B.m_deg; i++) {
		bit_B = mask_bit3(B, i);
		if (bit_B == 1) {
			C = add3(C, t_mul);
		}
		t_mul = mul_1_dig3(t_mul, t_mul, 2);
	}
	while ((C.arr[C.deg - 1] == 0) && (C.deg > 1)) {
		C.deg = C.deg - 1;
	}
	return C;
}

SROM sq3(SROM A, SROM B) {
	SROM res, temp;
	for (int i = 0; i < A.m_deg; i++) {
		res.bin[2 * i] = A.bin[i];
	}
	res.m_deg = (2 * A.m_deg) - 1;
	res.str = bin_hex3(res);
	res = read3(res);
	mod_gen3(res, B, temp);
	while ((temp.arr[temp.deg - 1] == 0) && (temp.deg > 1)) {
		temp.deg = temp.deg - 1;
	}
	return temp;
}

SROM pow3(SROM A, SROM B, SROM C) {
	SROM res, t_sq, t_mul;
	if (B.bin[B.m_deg - 1] != 0) {
		res = A;
		for (int i = B.m_deg - 2; i >= 0; i--) {
			t_sq = mult3(res, res);
			mod_gen3(t_sq, C, res);
			if (B.bin[i] == 1) {
				t_mul = mult3(res, A);
				mod_gen3(t_mul, C, res);
			}
		}
	}
	if (B.bin[B.m_deg - 1] == 0) {
		res.arr[0] = 1;
		res.deg = 1;
		return res;
	}
	while ((res.arr[res.deg - 1] == 0) && (res.deg > 1)) {
		res.deg = res.deg - 1;
	}
	return res;
}

SROM read4(SROM A){
	unsigned long long B = 0;
	A.m_deg = 0;
	int j = 0;
	*A.arr = { 0 };
	for (int i = (A.str.length() - 1); i >= 0; i--){
		if (A.str.length() > 8){
			while ((j != 8) && (i != -1)){
				if ((A.str[i] >= '0') && (A.str[i] <= '9')){
					B = A.str[i] - 48;
				}
				if ((A.str[i] >= 65) && (A.str[i] <= 70)){
					B = A.str[i] - 55;
				}
				A.arr[A.m_deg] = A.arr[A.m_deg] + (B)*pow(16, (((A.str.length() - 1) - i) % 8));
				i--;
				j++;
			}
			j = 1;
			if (i >= 0){
				if ((A.str[i] >= '0') && (A.str[i] <= '9')){
					B = A.str[i] - 48;
				}
				if ((A.str[i] >= 65) && (A.str[i] <= 70)){
					B = A.str[i] - 55;
				}
				A.m_deg = A.m_deg + 1;
				A.arr[A.m_deg] = A.arr[A.m_deg] + (B)*pow(16, (((A.str.length() - 1) - i) % 8));
			}
		}
		if (A.str.length() <= 8){
			if ((A.str[i] >= '0') && (A.str[i] <= '9')){
				B = A.str[i] - 48;
			}
			if ((A.str[i] >= 65) && (A.str[i] <= 70)){
				B = A.str[i] - 55;
			}
			A.arr[0] = A.arr[0] + (B)*pow(16, ((A.str.length() - 1) - i) % 8);
		}
	}
	A.m_deg = A.m_deg + 1;
	while ((A.arr[A.m_deg - 1] == 0) && (A.m_deg != 1)){
		A.m_deg = A.m_deg - 1;
	}
	return A;
}

string recort(SROM A){
	int temp = 0;
	char help = ' ';
	A.str = "";
	for (int i = 0; i < A.m_deg; i++){
		for (int j = 7; j >= 0; j--){
			temp = (A.arr[i]) % 16;
			if ((temp >= 0) && (temp <= 9)){
				help = temp + 48;
				A.str = help + A.str;
			}
			if ((temp >= 10) && (temp <= 15)){
				help = temp + 55;
				A.str = help + A.str;
			}
			A.arr[i] = A.arr[i] / 16;
		}
	}
	int j = 0;
	return A.str;
}

string bin_hex4(SROM A){
	int C = 0, B = 4;
	char help = ' ';
	A.str = "";
	for (int i = 0; i < ((A.m_deg / B) + 1); i++){
		C = A.bin[B * i];
		C = C + A.bin[B * i + 1] * 2;
		C = C + A.bin[B * i + 2] * 2 * 2;
		C = C + A.bin[B * i + 3] * 2 * 2 * 2;
		if ((C > 9) && (C < 16)) {
			help = C + 55;
			A.str = help + A.str;
		}
		if ((C > -1) && (C < 10)){
			help = C + 48;
			A.str = help + A.str;
		}
	}
	int j = 0;
	return A.str;
}

SROM add4(SROM A, SROM B){
	SROM C;
	if (A.m_deg < B.m_deg) {
		C.m_deg = B.m_deg;
	}
	if (A.m_deg >= B.m_deg) {
		C.m_deg = A.m_deg;
	}
	for (int i = 0; i < C.m_deg; i++){
		C.arr[i] = A.arr[i] ^ B.arr[i];
	}
	return C;
}

SROM sq4(SROM A){
	SROM B;
	for (int i = 0; i < A.m_deg - 1; i++){
		B.bin[i] = A.bin[i + 1];
	}
	B.bin[292] = A.bin[0];
	if (A.bin[0] == 1){
		B.m_deg = 293;
	}else{
		B.m_deg = A.m_deg - 1;
	}
	return B;
}

string mat(){
	string M = "";
	int A = 2 * 293 + 1;
	int I = 1, IJ = 0, II = 0, JJ = 0, IIJJ = 0;
	for (int i = 0; i < 293; i++){
		int J = 1;
		for (int j = 0; j < 293; j++){
			if ((((I + J - 1) % A) == 0) || (((I - J - 1) % A) == 0) || (((-I + J - 1) % A) == 0) || (((-I - J - 1) % A) == 0)){
				M = M + '1';
			}else{
				M = M + '0';
			}
			J = (2 * J) % A;
		}
		I = (2 * I) % A;
	}
	return M;
}

SROM left(SROM A){
	SROM B;
	for (int j= 1; j < 293; j++){
		B.bin[j] = A.bin[j - 1];
	}
	B.bin[0] = A.bin[292];
	B.m_deg = 293;
	return B;
}

SROM mul4(SROM A, SROM B, string C){
	SROM res;
	int column;
	for (int l = 0; l < 293; l++){
		int Bin[293] = { 0 };
		for (int j = 0; j < 293; j++){
			int temp = 0;
			int help = 0;
			for (int i = 0; i < 293; i++){
				int D = 0;
				D = C[(293 * i) + j] - 48;
				help = (D * A.bin[292 - i]);
				temp = temp + help;
			}
			column = temp % 2;
			Bin[j] = column;
		}
		int El = 0;
		for (int k = 0; k < 293; k++){
			El = (El ^ (Bin[k] * B.bin[292 - k]));
		}
		A = left(A);
		B = left(B);
		res.bin[292 - l] = El;
	}
	res.m_deg = 293;
	return res;
}

SROM pow4 (SROM A, SROM B, string C){
	SROM res, t_sq, t_mul;
	if (B.bin[B.m_deg - 1] == 0) {
		res = A;
		for (int i = B.m_deg - 2; i >= 0; i--) {
			res = sq4(res);
			if (B.bin[i] == 1) {
				res = mul4(res, A, C);
			}
		}
	}
	if (B.bin[B.m_deg - 1] == 0){
		res.arr[0] = 1;
		res.m_deg = 1;
		return res;
	}
	return res;
}

SROM inv4(SROM A, string M){
	SROM B, res, C;
	B = A;
	C = A;
	int k = 1;
	int m[8];
	m[0] = m[2] = m[3] = m[4] = m[5] = m[6] = 1;
	m[1] = m[7] = 0;
	for (int i = 1; i < 8; i++){
		for (int j = 0; j < k; j++){
			B = sq4(B);
		}
		B = mul4(B, C, M);
		k = 2 * k;
		if (m[i] == 1){
			B = sq4(B);
			B = mul4(B, A, M);
			k = k + 1;
		}
		C = B;
	}
	res = sq4(B);
	return res;
}

void lab1(SROM A, SROM B, int act){
	int choice, act1 = 1;
	SROM C, D;
	while (act1 == 1) {
		cout << endl;
		cout << " First lab" << endl;
		cout << " 1) A+B " << endl;
		cout << " 2) A-B " << endl;
		cout << " 3) A*B " << endl;
		cout << " 4) A/B " << endl;
		cout << " 5) A^B " << endl;
		cin >> choice;
		cout << endl;
		switch (choice) {
		case 1:
		{
			C = add(A, B, C);
			C.str = record(C);
			cout << "A+B: " << C.str << endl;
			cout << "If you want to countine, please press number 1, if not, please press other number: ";
			cin >> act1;
			break;
		}
		case 2:
		{
			C = sub(A, B, C, comp(A, C, 0));
			C.str = record(C);
			cout << "A-B: " << C.str << endl;
			cout << "If you want to countine, please press number 1, if not, please press other number: ";
			cin >> act1;
			break;
		}
		case 3:
		{
			C = mul(A, B, C);
			C.str = record(C);
			cout << "A*B: " << C.str << endl;
			cout << "If you want to countine, please press number 1, if not, please press other number: ";
			cin >> act1;
			break;
		}
		case 4:
		{
			divis(A, B, C, D);
			D.str = bin_hex(D);
			C.str = record(C);
			cout << "A\B: " << D.str << endl;
			cout << "If you want to countine, please press number 1, if not, please press other number: ";
			cin >> act1;
			break;
		}
		case 5:
		{
			D = bin_num(B);
			C = pow(A, D, C);
			C.str = record(C);
			cout << "A^B: " << C.str << endl;
			cout << "If you want to countine, please press number 1, if not, please press other number: ";
			cin >> act1;
			break;
		}
		default:
			break;
		}
	}
}

void lab2(SROM A, SROM B, int act) {
	int choice, act1 = 1;
	SROM C, D, E, F, base, Temp;
	while (act1 == 1) {
		cout << endl;
		cout << " Second lab" << endl;
		cout << " 1) Euclidean algorithm (A,B) " << endl;
		cout << " 2) Barets algorithm (A,B) " << endl;
		cout << " 3) Montgomery algorithm (A+B) mod N " << endl;
		cout << " 4) Montgomery algorithm (A-B) mod N " << endl;
		cout << " 5) Montgomery algorithm (A*B) mod N " << endl;
		cout << " 6) Montgomery algorithm (A^B) mod N " << endl;
		cout << " Your choice ";
		cin >> choice;
		cout << endl;
		switch (choice) {
		case 1:
		{
			C = gcd(A, B, C);
			C.str = record(C);
			cout << "Montgomery algorithm (A^B) mod N: " << C.str << endl;
			cout << "If you want to countine, please press number 1, if not, please press other number: ";
			cin >> act1;
			break;
		}
		case 2:
		{
			D = gcd(A, B, D);
			int ii = 0;
			C = lcm(A, B, D);
			C.str = record(C);
			cout << "Result: " << C.str;
			while (ii < 2) {
				if (ii == 0) {
					cout << endl;
				}
				ii++;
			}
			cout << "If you want to countine, please press number 1, if not, please press other number: ";
			cin >> act1;
			break;
		}
		case 3:
		{
			cout << "N: ";
			cin >> C.str;
			int ii = 0;
			C = read(C);
			while (ii < 2) {
				if (ii == 0) {
					cout << endl;
				}
				ii++;
			}
			D = mod_add(A, B, C);
			D.str = record(D);
			cout << "Result: " << D.str << endl;
			cout << "If you want to countine, please press number 1, if not, please press other number: ";
			cin >> act1;
			break;
		}
		case 4:
		{
			cout << "N: ";
			cin >> C.str;
			C = read(C);
			cout << endl;
			D = mod_sub(A, B, C);
			D.str = record(D);
			cout << "Result: " << D.str << endl;
			cout << "If you want to countine, please press number 1, if not, please press other number: ";
			cin >> act1;
			break;
		}
		case 5:
		{
			SROM  base, temp, C, res, D, E;
			int ii = 0;
			cout << "N: ";
			cin >> C.str;
			C = read(C);
			while (ii < 2) {
				if (ii == 0) {
					cout << endl;
				}
				ii++;
			}
			D = mul(A, B, D);
			D.lgth = 2 * C.lgth;
			base.lgth = 2;
			base.arr[1] = 1;
			base.arr[0] = 0;
			base = dig_high(base, (D.lgth - 1));
			divis(base, C, temp, E);
			E.str = bin_hex(E);
			E.lgth = 0;
			E = read(E);
			res = bar_red(D, C, E);
			res.str = record(res);
			cout << "Result: " << res.str;
			while (ii < 2) {
				if ((ii == 0)&&(ii==1)) {
					cout << endl;
				}
				ii++;
			}
			cout << "If you want to countine, please press number 1, if not, please press other number:";
			cin >> act1;
			break;
		}
		case 6:
		{
			cout << "N: ";
			cin >> C.str;
			int ii = 0;
			C = read(C);
			while (ii < 2) {
				if (ii == 0) {
					cout << endl;
				}
				ii++;
			}
			base.lgth = 1;
			base.arr[0] = 1;
			base = dig_high(base, (2 * C.lgth));
			divis(base, C, Temp, E);
			E.str = bin_hex(E);
			E.lgth = 0;
			E = read(E);
			F = bin_num(B);
			D = mod_pow_bar(A, F, C, E);
			D.str = record(D);
			cout << "Result: " << D.str << endl;
			cout << "If you want to countine, please press number 1, if not, please press other number: ";
			cin >> act1;
			break;
		}
		default:
			break;
		}
	}
}

void lab3(SROM A, SROM B, int act) {
	double D = 0;
	int ii =0;
	while (ii < 2) {
		if (ii == 0) {
			cout << endl;
		}
		ii++;
	}
	SROM gen, res, C;
	int choice, act1 = 1;
	gen.bin[293] = 1, gen.bin[11] = 1, gen.bin[6] = 1, gen.bin[1] = 1, gen.bin[0] = 1;
	gen.m_deg = 293;
	gen.str = bin_hex3(gen);
	gen = read3(gen);
	while (act1 == 1) {
		cout << "1) A+B " << endl;
		cout << "2) A*B " << endl;
		cout << "3) A^2 " << endl;
		cout << "4) A^(N) " << endl;
		cout << "5) A^(-1) " << endl << endl;
		cout << "choice ";
		cin >> choice;
		cout << endl;
		switch (choice) {
		case 1:
		{
			clock_t start = clock();
			res = add3(A, B);
			clock_t end = clock();
			res.str = record3(res);
			cout << "A+B = " << res.str << endl << "Time: ";
			D = (end - start) / CLOCKS_PER_SEC;
			cout << D << endl;
			cout << "If you want to countine, please press number 1, if not, please press other number:";
			cin >> act1;
			break;
		}
		case 2:
		{
			clock_t start = clock();
			C = mult3(A, B);
			mod_gen3(C, gen, res);
			clock_t end = clock();
			res.str = record3(res);
			cout << "A*B = " << res.str << endl << "Time: ";
			D = (end - start) / CLOCKS_PER_SEC;
			cout << D << endl;
			cout << "If you want to countine, please press number 1, if not, please press other number: ";
			cin >> act1;
			break;
		}
		case 3:
		{
			A = bin_num3(A);
			clock_t start = clock();
			res = sq3(A, gen);
			clock_t end = clock();
			res.str = record3(res);
			cout << "A^2 = " << res.str << endl << "Time : ";
			D = (end - start) / CLOCKS_PER_SEC;
			cout << D << endl;
			cout << "If you want to countine, please press number 1, if not, please press other number: ";
			cin >> act1;
			break;
		}
		case 4:
		{
			cout << " N: ";
			cin >> C.str;
			C = bin_num3(C);
			clock_t start = clock();
			res = pow3(A, C, gen);
			clock_t end = clock();
			res.str = record3(res);
			cout << endl;
			cout << "A^(N) = " << res.str << endl << "Time : ";
			D = (end - start) / CLOCKS_PER_SEC;
			cout << D << endl;
			cout << "If you want to countine, please press number 1, if not, please press other number: ";
			cin >> act1;
			break;
		}
		case 5:
		{
			C.m_deg = 293;
			cout << "  N: ";
			cin >> C.str;
			for (int i = 1; i < C.m_deg; i++) {
				C.bin[i] = 1;
			}
			clock_t start = clock();
			res = pow3(A, C, gen);
			clock_t end = clock();
			res.str = record3(res);
			cout << endl;
			cout << "A^(-1) =  " << res.str << endl << "Time : ";
			D = (end - start) / CLOCKS_PER_SEC;
			cout << D << endl;
			cout << "If you want to countine, please press number 1, if not, please press other number: ";
			cin >> act1;
			break;
		}
		default:
			break;
		}
	}
}

void lab4(SROM A, SROM B, int act) {
	SROM res, C;
	string M;
	M = mat();
	int choice, act1 = 1;
	while (act1 == 1)
	{
		cout << " 1) A+B" << endl;
		cout << " 2) A*B" << endl;;
		cout << " 3) A^2" << endl;;
		cout << " 4) A^(N)" << endl;;
		cout << " 5) A^(-1)" << endl;;
		cout << "choice ";
		cin >> choice;
		cout << endl;
		switch (choice){
		case 1:
		{
			res = add4(A, B);
			res.str = recort(res);
			cout << "A+B = " << res.str << endl;
			cout << endl;
			cout << "If you want to countine, please press number 1, if not, please press other number:";
			cin >> act1;
			break;
		}
		case 2:
		{
			A = bin_num3(A);
			B = bin_num3(B);
			res = mul4(A, B, M);
			res.str = bin_hex4(res);
			cout << "A*B = " << res.str << endl;
			cout << "If you want to countine, please press number 1, if not, please press other number:";
			cin >> act1;
			break;
		}
		case 3:
		{
			A = bin_num3(A);
			res = sq4(A);
			res.str = bin_hex4(res);
			cout << "A^2 = " << res.str << endl;
			cout << "If you want to countine, please press number 1, if not, please press other number:";
			cin >> act1;
			break;
		}
		case 4:
		{
			cout << "N: ";
			cin >> C.str;
			cout << endl;
			C = bin_num3(C);
			A = bin_num3(A);
			res = pow4(A, C, M);
			res.str = bin_hex4(res);
			cout << "A^(N) = " << res.str << endl;
			cout << "If you want to countine, please press number 1, if not, please press other number:";
			cin >> act1;
			break;
		}
		case 5:
		{
			A = bin_num3(A);
			res = inv4(A, M);
			res.str = bin_hex4(res);
			cout << "A^(-1) = " << res.str << endl;
			cout << "If you want to countine, please press number 1, if not, please press other number:";
			cin >> act1;
			break;
		}
		default:
			break;
		}
	}
}

int main() {
	SROM A, B;
	int act = 0;
	cout << " Select lab number" << endl << " 1) The first lab"<< endl <<" 2) The second lab" << endl << " 3) The third lab " << endl<< " 4) Number of labs: " << endl << "choice";
	cin >> act;
	switch (act){
	case 1:
	{
		cout << " You chose the first lab" << endl << " A: ";
		cin >> A.str;
		cout << endl;
		cout << " B: ";
		cin >> B.str;
		cout << endl;
		A = read(A);
		B = read(B);
		lab1(A, B, act);
	}
	case 2:
	{
		cout << " You chose the second lab " << endl << " A: ";
		cin >> A.str;
		cout << endl;
		cout << " B: ";
		cin >> B.str;
		cout << endl;
		A = read(A);
		B = read(B);
		lab2(A, B, act);
	}
	case 3:
	{
		cout << " You chose the third lab " << endl << " A: ";
		cin >> A.str;
		cout << endl;
		cout << "B: ";
		cin >> B.str;
		A = read3(A);
		B = read3(B);
		lab3(A, B,act);
	}
	case 4:
	{
		cout << " You chose the fourth lab " << endl << " A: ";
		cin >> A.str;
		cout << endl;
		cout << " B: ";
		cin >> B.str;
		cout << endl;
		A = read4(A);
		B = read4(B);
		lab4(A, B, act);
	}
	default:
		break;
	}
}