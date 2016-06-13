

/**********************************************************
 * 이 프로그램은 32비트의 c99기반 시그윈 에서만 작동됩니다.
 * 64비트에서 실행시 "segmantation fault"오류 출력  
 *********************************************************/

#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#define MAX 100
#define MAXI 50
#define MAXD 9

/* 복합연산(후위 연산법, 스택)은 인터넷 참고하였습니다.
 * 이중포인터 (->)또한 인터넷 참고하여 공부한뒤 활용했습니다. */

struct BigNum   //변수를 묶기 위해 구조체 사용(인터넷 참고)
{
	int i_digit[MAXI];
	int d_digit[MAXD];
	int i_total_digit;
	int d_total_digit;
	int i_digit_add[MAXI];
	int d_digit_add[MAXD];
	int sign;
};

struct stVar    //구조체사용 (인터넷 참고)
{
	char var;
	char* str;
};

struct stVar arrVar[10];
int bQuiet = 0;
int enter_number(char *input, struct BigNum *object);
int compare_number(struct BigNum *object, struct BigNum *object2);
int plus(struct BigNum *object, struct BigNum *object2, struct BigNum *object3);
int minus(struct BigNum *object, struct BigNum *object2, struct BigNum *object3);
int multiple(struct BigNum *object, struct BigNum *object2, struct BigNum *object3);
int divide(struct BigNum *object, struct BigNum *object2, struct BigNum *object3, struct BigNum *object4, struct BigNum *object5, struct BigNum *object6, int *d_total);
void print_var(char* k);
void postfix(char *dst, char *src);
char* calc(char *p);
void printResult(char* result);
void reverseString(char* s);
void reverseString(char* s)
{
	size_t size = strlen(s);
	char temp;
	for (size_t i = 0; i < size / 2; i++)
   	{
		temp = s[i];
		s[i] = s[(size - 1) - i];
		s[(size - 1) - i] = temp;
	}
}
char *strlwr(char *str)
{
	unsigned char *p = (unsigned char *)str;
	while (*p) 
	{
		*p = tolower(*p);
		p++;
	}
	return str;
}
int stack[MAX];        // 스택의 긴  통
int top;            // 스택의 상단
void init_stack(void) 
{
	top = -1;
} 

int push(int t) {

	if (top >= MAX - 1) {
		printf("\n    Stack overflow.");
		return -1;
	}

	stack[++top] = t;
	return t;
}

int pop(void) {
	if (top < 0) {
		printf("\n   Stack underflow.");
		return -1;
	}
	return stack[top--];
}

void print_stack(void) {
	int i;
	printf("\n Stack contents : TOP ----> Bottom\n");
	for (i = top; i >= 0; i--) {
		printf("%-6d", stack[i]);
	}
}

// 스택의 TOP의 값을 가져온다.
int get_stack_top(void) {
	return (top < 0) ? -1 : stack[top];
}

// 스택이 비어있는지 검사
int is_stack_empty(void) {
	return (top < 0);
}

// k 가 연산자인지 판단한다.
int is_operator(int k) {
	return (k == '+' || k == '-' || k == '*' || k == '/' || k == '%');
}

int has_operator(char* k)
{
	int res = 0;
	while(*k)
	{
		if (is_operator(*k))
		{
			res = 1;
			break;
		}
		k++;
	}
	return res;
}

char *replaceAll(char *s, const char *olds, const char *news) {
	char *result, *sr;
	size_t i, count = 0;
	size_t oldlen = strlen(olds); if (oldlen < 1) return s;
	size_t newlen = strlen(news);


	if (newlen != oldlen) {
		for (i = 0; s[i] != '\0';) {
			if (memcmp(&s[i], olds, oldlen) == 0) count++, i += oldlen;
			else i++;
		}
	}
	else i = strlen(s);


	result = (char *)malloc(i + 1 + count * (newlen - oldlen));
	if (result == NULL) return NULL;


	sr = result;
	while (*s) {
		if (memcmp(s, olds, oldlen) == 0) {
			memcpy(sr, news, newlen);
			sr += newlen;
			s += oldlen;
		}
		else *sr++ = *s++;
	}
	*sr = '\0';

	return result;
}
void input_var_after_calc(char *k)
{
	char var = 0;
	char* tk;
	char* str;
	int nTemp = 0;
	tk = replaceAll(k, " ", "");
	while (*tk)
	{
		if (var == 0 && is_firstalpha(tk))
		{
			var = *tk;
			break;
		}
		tk++;
		nTemp++;
	}
	tk += 2;
	str = tk;
	char pf[256];
	postfix(pf, str);
	char* res = calc(pf);

	for (int i = 0; i < 10; i++)
	{
		if (arrVar[i].var == var)
		{
			return;
		}
		if (arrVar[i].var == 0)
		{
			arrVar[i].var = var;
			arrVar[i].str = res;
			printResult(res);
			break;
		}
	}

}
void input_var(char *k)
{
	char var = 0;
	char* tk;
	char* str;
	int nTemp = 0;
	tk = replaceAll(k, " ", "");
	while (*tk)
	{
		if ( var == 0 && is_firstalpha(tk))
		{
			var = *tk;
			break;
		}		
		tk++;
		nTemp++;
	}
	tk+=2;
	str = tk;
	for (int i = 0; i < 10; i++)
	{
		if (arrVar[i].var == var)
		{
			return;
		}
		if (arrVar[i].var == 0)
		{
			arrVar[i].var = var;
			arrVar[i].str = str;
			if(bQuiet==0)
				printResult(str);
			break;
		}
	}
}
void savevar()     //변수저장함수 
{
	FILE* pf = fopen("var.txt","w+");
	for (int i = 0; i < 10; i++)
	{
		if (arrVar[i].var != 0)
		{
			printf("%c = %s\n", arrVar[i].var, arrVar[i].str);
			fprintf(pf,"%c = %s\n", arrVar[i].var, arrVar[i].str);
		}
	}
	fclose(pf);
}
void loadvar()    //변수로드함수 
{
	FILE* pf = fopen("var.txt","rt");
	char s[128];
	if (pf == 0)
	{
		printf("정의된 변수 없음\n");
		return;
	}

	while (fgets(s, 128, pf) != NULL) {
		printf(s); // 한 줄씩 화면에 출력
		char* tp = replaceAll(s, "\n", "");
		input_var(tp);
	}

	fclose(pf);
}
void print_arrVar()  //var 시 출력함수
{
	for (int i = 0; i < 10; i++)
	{		 
		if( arrVar[i].var != 0 )
			printf("%c = %s\n", arrVar[i].var, arrVar[i].str); 		 
	}
}
void print_var(char *k)  //변수 1개만 입력시 저장된값 출력
{
	int nFind = 0;
	for (int i = 0; i < 10; i++)
	{
		if (arrVar[i].var == *k)
		{
			printf("= %s\n", arrVar[i].str);
			nFind = 1;
			break;
		}		
	}
	if (nFind == 0)
		printf("= undefined.\n");
}

int is_alpha(char *k)
{
	if (strlen(k) != 1)
		return 0;
	return (*k >= 'a' && *k <= 'z');
}
int is_firstalpha(char *k) 
{
	return (*k >= 'a' && *k <= 'z');
}

int is_input(char *k)
{
	int nCnt = 0;
	while (*k)
	{
		if (*k == '=')
		{
			nCnt++;
		}
		k++;
	}
	return (nCnt == 1);
}
int is_digit(int k)
{
	return (k >= '0' && k <= '9');
}

int is_var(char* k)
{
	int res = 0;
	for (int i = 0; i < 10; i++)
	{
		if (arrVar[i].var == k)
		{
			res = 1;
			break;
		}
	}
	return res;
}
char* varToStr(char *s)
{  
	for (int i = 0; i < 10; i++)
	{
		if (arrVar[i].var != 0)
		{
			char* t = &arrVar[i].var;
			s = replaceAll(s, t, arrVar[i].str);
		}
	}
	return s;
}
int is_legal(char *s) {
	int res = 1;
	while (*s) {

		// 처음 공백 넘어가기
		while (*s == ' ') {
			s++;
		}

		if ( !is_operator(*s) && !is_digit(*s) && !is_var(*s) ) {
			res = 0;
			break;
		}
		s++;
	}
	return res;
}

// 연산자의 우선순위를 수치로 변환해준다.
int precedence(int op) {
	if (op == '+' || op == '-') return 0;
	if (op == '*' || op == '/' || op == '%') return 1;
	else return 3;
}

// 중위표기법을 후위표기법으로 변환
void postfix(char *dst, char *src) {
	char c;
	init_stack();
	while (*src) {
		if (*src == '-' && *(src + 1) != ' ')
		{
			do {
				*dst++ = *src++;
			} while (*src >= '0' && *src <= '9');
			*dst++ = ' ';
		}
		else if (is_operator(*src)) {
			while (!is_stack_empty() &&
					precedence(get_stack_top()) >= precedence(*src)) {
				*dst++ = pop();
				*dst++ = ' ';
			}
			push(*src);
			src++;
		}
		else if (*src >= '0' && *src <= '9') {
			do {
				*dst++ = *src++;
			} while (*src >= '0' && *src <= '9' || *src == '.');
			*dst++ = ' ';
		}
		else {
			src++;
		}
	}

	while (!is_stack_empty()) {
		*dst++ = pop();
		*dst++ = ' ';
	}
	dst--;
	*dst = 0;
}

// 후위표기법을 계산한다.
char* calc(char *p) {

	struct BigNum object[6];

	int i,cnt;
	init_stack();
	while (*p) {
		if (*p >= '0' && *p <= '9') {
			i = 0;
			cnt = 0;
			char* np = (char*)malloc(sizeof(char) * 70);
			do {
				i = i * 10 + *p - '0';
				np[cnt++] = *p;
				p++;
			} while (*p >= '0' && *p <= '9' || *p=='.');
			np[cnt] = 0;
			push(np);
		}		
		else if (*p == '-' && (*(p + 1) != 0 && *(p + 1) != ' '))
		{
			i = 0;
			cnt = 0;
			char* np = (char*)malloc(sizeof(char) * 70);
			do {
				i = i * 10 + *p - '0';
				np[cnt++] = *p;
				p++;
			} while (*p >= '0' && *p <= '9');
			np[cnt] = 0;
			push(np);
		}
		else if (*p == '+') {
			enter_number((char*)pop(), &object[0]);
			enter_number((char*)pop(), &object[1]);

			if (object[0].sign>0 && object[1].sign>0)
			{
				plus(&object[0], &object[1], &object[2]);
			}
			else if (object[0].sign <0 && object[1].sign<0)
			{
				plus(&object[0], &object[1], &object[2]);
			}
			else if (object[0].sign>0 && object[1].sign<0)
			{
				minus(&object[0], &object[1], &object[2]);
			}
			else
			{
				minus(&object[1], &object[0], &object[2]);
			} 
			cnt = 0;
			char* np = (char*)malloc(sizeof(char) * 70);

			if (object[2].sign < 0)
			{
				np[cnt++] = '-';
			}
			for (i = 0; i<object[2].i_total_digit; i++)
			{ 
				np[cnt++] = object[2].i_digit[object[2].i_total_digit - i - 1] + 48;
			}
			if (object[2].d_total_digit>0)
			{
				np[cnt++] = '.';
			}
			for (i = 0; i<object[2].d_total_digit; i++)
			{
				np[cnt++] = object[2].d_digit[object[2].d_total_digit - i - 1] + 48;
			}

			np[cnt] = 0;
			// 출력
			push(np);

			p++;
		} 
		else if (*p == '-' && ( *(p+1) == 0 || *(p+1) == ' ')  ) {
			enter_number((char*)pop(), &object[1]);
			enter_number((char*)pop(), &object[0]);
			cnt = 0;
			char* np = (char*)malloc(sizeof(char) * 70);

			if (object[0].sign > 0 && object[1].sign > 0)
			{
				minus(&object[0], &object[1], &object[2]);
			}
			else if (object[0].sign > 0 && object[1].sign < 0)
			{
				plus(&object[0], &object[1], &object[2]);
			}
			else if (object[0].sign < 0 && object[1].sign > 0)
			{
				plus(&object[0], &object[1], &object[2]);
			}
			else
			{
				minus(&object[0], &object[1], &object[2]);
			}

			if (object[2].sign < 0)
			{
				np[cnt++] = '-';
			}
			for (i = 0; i<object[2].i_total_digit; i++)
			{				
				np[cnt++] = object[2].i_digit[object[2].i_total_digit - i - 1] + 48;
			}
			if (object[2].d_total_digit>0)
			{
				np[cnt++] = '.';
			}
			for (i = 0; i<object[2].d_total_digit; i++)
			{				
				np[cnt++] = object[2].d_digit[object[2].d_total_digit - i - 1] + 48;
			}

			np[cnt] = 0;
			push(np);
			p++;
		}
		else if (*p == '*') {
			enter_number((char*)pop(), &object[0]);
			enter_number((char*)pop(), &object[1]);
			multiple(&object[0], &object[1], &object[2]);

			cnt = 0;
			char* np = (char*)malloc(sizeof(char) * 70);

			if (object[2].sign < 0)
			{
				np[cnt++] = '-';
			}
			if (object[2].i_total_digit>100)
			{
				for (i = 0; i<object[2].i_total_digit - 100; i++)
				{
					np[cnt++] = object[2].i_digit_add[object[2].i_total_digit - 100 - 1 - i] + 48;
				}
				for (i = 0; i<100; i++)
				{
					np[cnt++] = object[2].i_digit_add[object[2].i_total_digit - 100 - 1 - i] + 48;
				}
			}
			else
			{
				for (i = 0; i<object[2].i_total_digit; i++)
				{
					np[cnt++] = object[2].i_digit[object[2].i_total_digit - i - 1] + 48;
				}
			}
			if (object[2].d_total_digit>0)
			{
				np[cnt++] = '.';
			}
			if (object[2].d_total_digit>100)
			{
				for (i = 0; i<100; i++)
				{
					np[cnt++] = object[2].d_digit[99 - i] + 48;
				}
				for (i = 0; i<object[2].d_total_digit - 100; i++)
				{
					np[cnt++] = object[2].d_digit_add[object[2].d_total_digit - 100 - 1 - i] + 48;
				}
			}
			else
			{
				for (i = 0; i<object[2].d_total_digit; i++)
				{
					np[cnt++] = object[2].d_digit[object[2].d_total_digit - i - 1] + 48;
				}
			}

			np[cnt] = 0;
			push(np);

			p++;
		}
		else if (*p == '/') {
			enter_number((char*)pop(), &object[1]);
			enter_number((char*)pop(), &object[0]);
			cnt = 0;
			int k = 9;
			char* np = (char*)malloc(sizeof(char) * 70);

			divide(&object[0], &object[1], &object[2], &object[3], &object[4], &object[5], &k);

			if (object[2].sign < 0)
			{
				np[cnt++] = '-';
			}
			if (object[2].i_total_digit>100)
			{
				for (i = 0; i<object[2].i_total_digit - 100; i++)
				{
					np[cnt++] = object[2].i_digit_add[object[2].i_total_digit - 100 - 1 - i] + 48;
				}
				for (i = 0; i<100; i++)
				{
					np[cnt++] = object[2].i_digit[99 - i] + 48;
				}
			}
			else
			{
				for (i = 0; i<object[2].i_total_digit; i++)
				{					
					np[cnt++] = object[2].i_digit[object[2].i_total_digit - i - 1] + 48;
				}
			}
			if (object[2].d_total_digit>0)
			{
				np[cnt++] = '.';
			}
			if (object[2].d_total_digit>100)
			{
				for (i = 0; i<100; i++)
				{
					np[cnt++] = object[2].d_digit[99 - i] + 48;
				}
				for (i = 0; i<object[2].d_total_digit - 100; i++)
				{
					np[cnt++] = object[2].d_digit_add[object[2].d_total_digit - 100 - 1 - i] + 48;
				}
			}
			else
			{
				for (i = 0; i<object[2].d_total_digit; i++)
				{
					np[cnt++] = object[2].d_digit[object[2].d_total_digit - i - 1] + 48;
				}
			}

			np[cnt] = 0;
			push(np);
			p++;
		}
		else if (*p == '%') {
			cnt = 0;
			char* np = (char*)malloc(sizeof(char) * 70);

			long long mod = atoi((char*)pop());
			char* num= (char*)pop();

			long long remainder = 0;
			for (int i = 0; num[i] != '\0'; ++i)
				remainder = (remainder * 10 + num[i] - '0') % mod;

			while (1)
			{
				if (remainder < 10)
				{
					np[cnt++] = remainder + 48;
					np[cnt] = 0;
					break;
				}
				else
				{
					np[cnt++] = remainder % 10 + 48;
					remainder /= 10;
				}

			}

			reverseString(np);
			push(np);
			p++;
		}
		else {
			p++;
		}
	}
	return pop();
}


int enter_number(char *input, struct BigNum *object)     //숫자를 입력하기 위한 함수(단항, 점까지 포함)
{
	int i, j, l;
	i = j = l = 0;
	object->i_total_digit = 0;
	object->d_total_digit = 0;
	if (*input == '-')
	{
		input++;
		while (*input != '.'&&*input != '\0')
		{
			i++;
			input++;
		}
		j = i;
		input = input - i;
		i = 0;
		for (i = 0; i<j; i++)
		{
			object->i_digit[j - i - 1] = (int)*input - 48;
			object->i_total_digit++;
			input++;
		}
		if (*input != '\0')
		{
			input++;
		}
		while (*input)
		{
			object->d_total_digit++;
			l++;
			input++;
		}
		input = input - l;
		for (i = 0; i<l; i++)
		{
			object->d_digit[l - i - 1] = (int)*input - 48;
			input++;
		}
		input = input - object->i_total_digit - object->d_total_digit - 2;
		l = 0;
		object->sign = -1;
	}
	else
	{
		while (*input != '.' && *input != '\0')
		{
			i++;
			input++;
		}
		j = i;
		input = input - i;
		i = 0;
		for (i = 0; i<j; i++)
		{
			object->i_digit[j - i - 1] = (int)*input - 48;
			object->i_total_digit++;
			input++;
		}
		if (*input == '.')
		{
			input++;
		}
		while (*input)
		{
			object->d_total_digit++;
			l++;
			input++;
		}
		input = input - l;
		for (i = 0; i<l; i++)
		{
			object->d_digit[l - i - 1] = (int)*input - 48;
			input++;
		}
		input = input - object->i_total_digit - object->d_total_digit - 1;
		l = 0;
		object->sign = 1;
	}
	return 0;
}
int compare_number(struct BigNum *object, struct BigNum *object2)   // 수 비교 함수
{
	int i, j, k;
	j = 0; k = 0;
	for (i = 0; i<400; i++)
	{
		if (object->i_total_digit > object2->i_total_digit)
		{
			j = 1;
			k = 1;
			break;
		}
		else if (object2->i_total_digit > object->i_total_digit)
		{
			j = 1;
			k = 2;
			break;
		}
		else if (object2->i_total_digit == object->i_total_digit)
		{
			if (object->i_digit[object->i_total_digit - i - 1] > object2->i_digit[object2->i_total_digit - i - 1])
			{
				j = 1;
				k = 1;
				break;
			}
			else if (object2->i_digit[object2->i_total_digit - i - 1] > object->i_digit[object->i_total_digit - i - 1])
			{
				j = 1;
				k = 2;
				break;
			}
			else if (object2->i_digit[object2->i_total_digit - i - 1] == object->i_digit[object->i_total_digit - i - 1])
			{
				if (i>object->i_total_digit || i>object2->i_total_digit)
				{
					i = 0;
					break;
				}
				else if (object->i_digit[0] == 0 && object->i_total_digit == 1)
				{
					i = 0;
					break;
				}
			}
		}
	}
	if (j == 0)
	{
		for (;;)
		{
			if (object->d_digit[object->d_total_digit - 1 - i] > object2->d_digit[object2->d_total_digit - 1 - i])
			{
				j = 1;
				k = 1;
				break;
			}
			else if (object2->d_digit[object2->d_total_digit - 1 - i] > object->d_digit[object->d_total_digit - 1 - i])
			{
				j = 1;
				k = 2;
				break;
			}
			else
			{
				if (i<object->d_total_digit && i<object2->d_total_digit)
				{
					i++;
				}
				else
				{
					if (object->d_total_digit == object2->d_total_digit)
					{
						j = 1;
						k = 0;
						break;
					}
					else if (object->d_total_digit > object2->d_total_digit)
					{
						j = 1;
						k = 1;
						break;
					}
					else
					{
						j = 1;
						k = 2;
						break;
					}
				}
			}
		}
	}
	return k;
}
int plus(struct BigNum *object, struct BigNum *object2, struct BigNum *object3)   //'+'함수
{
	int i, j, k, m;
	m = 0;
	if (object->d_total_digit > object2->d_total_digit)
	{
		for (j = 0; j<object2->d_total_digit; j++)
		{
			object3->d_digit[j + object2->d_total_digit] = object2->d_digit[j] + object->d_digit[j + object2->d_total_digit];
		}
		object3->d_total_digit = object->d_total_digit;
	}
	else if (object->d_total_digit == object2->d_total_digit)
	{
		for (i = 0; i<object2->d_total_digit; i++)
		{
			object3->d_digit[i] = object->d_digit[i] + object2->d_digit[i];
		}
		object3->d_total_digit = object2->d_total_digit;
	}
	else
	{
		k = object2->d_total_digit - object->d_total_digit;
		for (j = 0; j<object->d_total_digit; j++)
		{
			object3->d_digit[j + k] = object->d_digit[j] + object2->d_digit[j + k];
		}
		for (j = 0; j<object2->d_total_digit; j++)
		{
			object3->d_digit[j] = object2->d_digit[j];
		}
		object3->d_total_digit = object2->d_total_digit;
	}


	if (object->i_total_digit>object2->i_total_digit)
	{
		for (j = 0; j<object2->i_total_digit; j++)
		{
			object3->i_digit[j] = object->i_digit[j] + object2->i_digit[j];
		}
		for (j = object2->i_total_digit; j<object->i_total_digit; j++)
		{
			object3->i_digit[j] = object->i_digit[j];
		}
		object3->i_total_digit = object->i_total_digit;
	}
	else if (object->i_total_digit == object2->i_total_digit)
	{
		for (j = 0; j<object->i_total_digit; j++)
		{
			object3->i_digit[j] = object->i_digit[j] + object2->i_digit[j];
		}
		object3->i_total_digit = object2->i_total_digit;
	}
	else
	{
		for (j = 0; j<object->i_total_digit; j++)
		{
			object3->i_digit[j] = object->i_digit[j] + object2->i_digit[j];
		}
		for (j = object->i_total_digit; j<object2->i_total_digit; j++)
		{
			object3->i_digit[j] = object2->i_digit[j];
		}
		object3->i_total_digit = object2->i_total_digit;
	}
	for (j = 0; j<object3->d_total_digit; j++)
	{
		if (object3->d_digit[j]>9)
		{
			object3->d_digit[j] = object3->d_digit[j] - 10;
			if (j == object3->d_total_digit - 1)
			{
				if (object3->i_digit[0] >= 0 && object3->i_digit[0] < 20)
				{
					object3->i_digit[0] = object3->i_digit[0] + 1;
				}
				else
				{
					object3->i_digit[0] = 1;
				}
			}
			else
			{
				object3->d_digit[j + 1] = object3->d_digit[j + 1] + 1;
			}
		}
	}
	for (j = 0; j<object3->i_total_digit; j++)
	{
		if (object3->i_digit[j]>9)
		{
			object3->i_digit[j] = object3->i_digit[j] - 10;
			if (j == 99)
			{
				object3->i_digit_add[0] = 1;
				object3->i_total_digit++;
			}
			else
			{
				if (object3->i_digit[j + 1]<20 && object3->i_digit[j + 1] >= 0)
				{
					object3->i_digit[j + 1]++;
				}
				else
				{
					object3->i_digit[j + 1] = 1;
					object3->i_total_digit++;
				}

			}
		}
	}
	if (object3->d_digit[0] == 0)
	{
		object3->d_total_digit--;
		for (j = 1; j<object3->d_total_digit; j++)
		{
			if (object3->d_digit[j] == 0)
			{
				object3->d_total_digit--;
			}
			else
			{
				break;
			}
		}
	}
	object3->sign = object->sign;
	return 0;
}
int minus(struct BigNum *object, struct BigNum *object2, struct BigNum *object3)     //'-'함수
{
	int i=0, j=0, k=0;
	k = compare_number(object, object2);
	if (object->i_total_digit>object2->i_total_digit)
	{
		if (object->d_total_digit>object2->d_total_digit)
		{
			object3->i_total_digit = object2->i_total_digit;
			object3->d_total_digit = object->d_total_digit;
		}
		else
		{
			object3->i_total_digit = object2->i_total_digit;
			object3->d_total_digit = object2->d_total_digit;
		}
	}
	else if (object->i_total_digit == object2->i_total_digit)
	{
		if (object->d_total_digit>object2->d_total_digit)
		{
			object3->i_total_digit = object->i_total_digit;
			object3->d_total_digit = object->d_total_digit;
		}
		else
		{
			object3->i_total_digit = object->i_total_digit;
			object3->d_total_digit = object2->d_total_digit;
		}
	}
	else
	{
		if (object->d_total_digit>object2->d_total_digit)
		{
			object3->i_total_digit = object->i_total_digit;
			object3->d_total_digit = object->d_total_digit;
		}
		else
		{
			object3->i_total_digit = object->i_total_digit;
			object3->d_total_digit = object2->d_total_digit;
		}
	}
	for (i = 0; i<object3->i_total_digit; i++)
	{
		object3->i_digit[i] = object->i_digit[i] - object2->i_digit[i];
	}
	if (object->i_total_digit>object2->i_total_digit)
	{
		for (i = object3->i_total_digit; i<object->i_total_digit; i++)
		{
			object3->i_digit[i] = object->i_digit[i];
		}
		object3->i_total_digit = object->i_total_digit;
	}
	else
	{
		for (i = object3->i_total_digit; i<object2->i_total_digit; i++)
		{
			object3->i_digit[i] = 0 - object2->i_digit[i];
			j++;
		}
		object3->i_total_digit = object2->i_total_digit;
	}
	if (object->d_total_digit>object2->d_total_digit)
	{
		j = object->d_total_digit - object2->d_total_digit;
	}
	else
	{
		j = object2->d_total_digit - object->d_total_digit;
	}
	if (object->d_total_digit>object2->d_total_digit)
	{
		for (i = 0; i<j; i++)
		{
			object3->d_digit[i] = object->d_digit[i];
		}
		for (i = j; i<object3->d_total_digit; i++)
		{
			object3->d_digit[i] = object->d_digit[i] - object2->d_digit[i - j];
		}
	}
	else if (object->d_total_digit == object2->d_total_digit)
	{
		for (i = 0; i<object->d_total_digit; i++)
		{
			object3->d_digit[i] = object->d_digit[i] - object2->d_digit[i];
		}
	}
	else
	{
		for (i = 0; i<j; i++)
		{
			object3->d_digit[i] = 0 - object2->d_digit[i];
		}
		for (i = j; i<object3->d_total_digit; i++)
		{
			object3->d_digit[i] = object->d_digit[i - j] - object2->d_digit[i];
		}
	}
	if (k == 1)
	{
		for (i = 0; i<object3->d_total_digit; i++)
		{
			if (object3->d_digit[i]<0)
			{
				object3->d_digit[i] = object3->d_digit[i] + 10;
				if (i == 99 || i == object3->d_total_digit - 1)
				{
					object3->i_digit[0]--;
				}
				else
				{
					object3->d_digit[i + 1]--;
				}
			}
		}
		for (i = 0; i<object3->i_total_digit; i++)
		{
			if (object3->i_digit[i]<0)
			{
				object3->i_digit[i] = object3->i_digit[i] + 10;
				object3->i_digit[i + 1]--;
			}
		}
		object3->sign = object->sign;
	}
	else if (k == 2)
	{
		for (i = 0; i<object3->d_total_digit; i++)
		{
			object3->d_digit[i] = 0 - object3->d_digit[i];
			if (object3->d_digit[i]<0)
			{
				if (i == 99)
				{
					object3->i_digit[0]--;
				}
				else if (i == object3->d_total_digit - 1)
				{
					object3->d_digit[i] = object3->d_digit[i] + 10;
					object3->i_digit[0]++;
				}
				else
				{
					object3->d_digit[i] = object3->d_digit[i] + 10;
					object3->d_digit[i + 1]++;
				}
			}
		}
		for (i = 0; i<object3->i_total_digit; i++)
		{
			object3->i_digit[i] = 0 - object3->i_digit[i];
			if (object3->i_digit[i]<0)
			{
				object3->i_digit[i] = object3->i_digit[i] + 10;
				object3->i_digit[i + 1]++;
			}
		}
		object3->sign = 0 - object->sign;
	}
	for (i = 0; i<object3->d_total_digit; i++)
	{
		if (object3->d_digit[i] == 0)
		{
			object3->d_total_digit--;
		}
		else
		{
			break;
		}
	}
	j = 0;
	for (i = 0; i<object3->i_total_digit; i++)
	{

		if (object3->i_digit[object3->i_total_digit - 1 - i] == 0)
		{
			j++;
		}
		else
		{
			object3->i_total_digit = object3->i_total_digit - j;
			j = 0;
			break;
		}
	}
	return 0;
}
int multiple(struct BigNum *object, struct BigNum *object2, struct BigNum *object3)           //'*'함수
{
	int i, j, k, l, m, n, o;
	int obj_num[200], obj2_num[200], obj3_num[400];
	for (i = 0; i<object->d_total_digit; i++)
	{
		obj_num[i] = object->d_digit[i];
	}
	for (i = 0; i<object->i_total_digit; i++)
	{
		obj_num[i + object->d_total_digit] = object->i_digit[i];
	}
	for (i = 0; i<object2->d_total_digit; i++)
	{
		obj2_num[i] = object2->d_digit[i];
	}
	for (i = 0; i<object2->i_total_digit; i++)
	{
		obj2_num[i + object2->d_total_digit] = object2->i_digit[i];
	}
	object3->d_total_digit = object->d_total_digit + object2->d_total_digit;
	object3->i_total_digit = object->i_total_digit + object2->i_total_digit;
	if (object->i_digit[object->i_total_digit - 1] * object2->i_digit[object2->i_total_digit - 1])
	{
		object3->i_total_digit++;
	}
	for (i = 0; i<object3->i_total_digit + object3->d_total_digit; i++)
	{
		obj3_num[i] = 0;
	}
	for (i = 0; i<object2->d_total_digit + object2->i_total_digit; i++)
	{
		for (j = 0; j<object->d_total_digit + object->i_total_digit; j++)
		{
			k = obj_num[j] * obj2_num[i];
			l = k / 10;
			n = k % 10;
			obj3_num[i + j] = obj3_num[i + j] + n;
			obj3_num[i + j + 1] = obj3_num[i + j + 1] + l;
			if (obj3_num[i + j]>9)
			{
				obj3_num[i + j] = obj3_num[i + j] - 10;
				obj3_num[i + j + 1]++;
			}
			if (obj3_num[i + j + 1]>9)
			{
				obj3_num[i + j + 1] = obj3_num[i + j + 1] - 10;
				obj3_num[i + j + 2]++;
			}
		}
	}
	if (object3->d_total_digit>100 && object3->i_total_digit>100)
	{
		for (i = 0; i<object3->d_total_digit - 100; i++)
		{
			object3->d_digit_add[i] = obj3_num[i];
		}
		for (i = 0; i<100; i++)
		{
			object3->d_digit[i] = obj3_num[i + object3->d_total_digit - 100];
			object3->i_digit[i] = obj3_num[i + object3->d_total_digit];
		}
		for (i = 0; i<object3->i_total_digit - 100; i++)
		{
			object3->i_digit_add[i] = obj3_num[i + object3->d_total_digit + object3->i_total_digit - 100];
		}
	}
	else if (object3->d_total_digit>100 && object3->i_total_digit <= 100)
	{
		for (i = 0; i<object3->d_total_digit - 100; i++)
		{
			object3->d_digit_add[i] = obj3_num[i];
		}
		for (i = 0; i<100; i++)
		{
			object3->d_digit[i] = obj3_num[i + object3->d_total_digit - 100];
		}
		for (i = 0; i<object3->i_total_digit; i++)
		{
			object3->i_digit[i] = obj3_num[i + object3->d_total_digit];
		}
	}
	else if (object3->d_total_digit <= 100 && object3->i_total_digit>100)
	{
		for (i = 0; i<object3->d_total_digit; i++)
		{
			object3->d_digit[i] = obj3_num[i];
		}
		for (i = 0; i<100; i++)
		{
			object3->i_digit[i] = obj3_num[i + object3->d_total_digit];
		}
		for (i = 0; i<object3->i_total_digit - 100; i++)
		{
			object3->i_digit_add[i] = obj3_num[i + object3->d_total_digit + object3->i_total_digit - 100];
		}
	}
	else
	{
		for (i = 0; i<object3->d_total_digit; i++)
		{
			object3->d_digit[i] = obj3_num[i];
		}
		for (i = 0; i<object3->i_total_digit; i++)
		{
			object3->i_digit[i] = obj3_num[i + object3->d_total_digit];
		}
	}
	if (object3->d_total_digit>100)
	{
		for (i = 0; i<object3->d_total_digit - 100; i++)
		{
			if (object3->d_digit_add[i] == 0)
			{
				for (j = 0; j<object3->d_total_digit - 100; j++)
				{
					object3->d_digit_add[j] = object3->d_digit_add[j + 1];
				}
				object3->d_total_digit--;
			}
			else
			{
				m = 0;
				break;
			}
		}
		if (m != 0)
		{
			for (i = 0; i<100; i++)
			{
				if (object3->d_digit[i] == 0)
				{
					for (j = 0; j<object3->d_total_digit; j++)
					{
						object3->d_digit[j] = object3->d_digit[j + 1];
					}
					object3->d_total_digit--;
				}
				else
				{
					m = 1;
					break;
				}
			}
		}
	}
	else
	{
		for (i = 0; i<object3->d_total_digit; i++)
		{
			if (object3->d_digit[i] == 0)
			{
				for (j = 0; j<object3->d_total_digit; j++)
				{
					object3->d_digit[j] = object3->d_digit[j + 1];
				}
				object3->d_total_digit--;
			}
			else
			{
				break;
			}
		}
	}
	if (object3->i_total_digit>100)
	{
		for (i = 0; i<object3->i_total_digit - 100; i++)
		{
			if (object3->i_digit_add[i] == 0)
			{
				object3->i_total_digit--;
			}
			else
			{
				m = 0;
				break;
			}
		}
		if (m != 0)
		{
			for (i = 0; i<100; i++)
			{
				if (object3->i_digit[99 - i] == 0)
				{
					object3->i_total_digit--;
				}
				else
				{
					m = 1;
					break;
				}
			}
		}
	}
	else
	{
		o = object3->i_total_digit;
		for (i = 0; i<object3->i_total_digit; i++)
		{
			if (object3->i_digit[o - 1 - i] == 0)
			{
				object3->i_total_digit--;
			}
			else
			{
				break;
			}
		}
	}
	object3->sign = object->sign * object2->sign;
	return 0;
}
int divide(struct BigNum *object, struct BigNum *object2, struct BigNum *object3, struct BigNum *object4, struct BigNum *object5, struct BigNum *object6, int *d_total)   //'/'함수
{
	int i, j, k, l;
	int a, b, c, d, e;
	a = object->sign;
	b = object2->sign;
	c = d = 0; e = 0;
	j = k = l = 0;
	object->sign = 1; object2->sign = 1;
	object3->i_total_digit = object3->d_total_digit = 0;
	*object6 = *object;
	*object4 = *object2;
	if (object->i_total_digit == 1 && object->i_digit[0] == 0)
	{
		d++;
		object->i_digit[0] = object->d_digit[object->d_total_digit - 1];
		for (i = 0; i<object->d_total_digit; i++)
		{
			object->d_digit[object->d_total_digit - 1 - i] = object->d_digit[object->d_total_digit - 1 - i];
		}
		object->d_digit[0] = 0;
	}
	if (object2->i_total_digit == 1 && object2->i_digit[0] == 0)
	{
		for (i = 0; i<100; i++)
		{
			if (object4->d_digit[object->d_total_digit - 1 - i] == 0)
			{
				e++;
			}
			else
			{
				break;
			}
		}
		object4->i_digit[0] = object4->d_digit[object4->d_total_digit - 1 - e];
		for (i = 0; i<object4->d_total_digit; i++)
		{
			object4->d_digit[object4->d_total_digit - 1 - i] = object4->d_digit[object4->d_total_digit - 1 - i - e];
		}
		for (i = 0; i<e; i++)
		{
			object4->d_digit[i] = 0;
		}
		if (e == 0)
		{
			object4->d_digit[0] = 0;
			d--;
		}
		d = d - e;
	}
	for (i = 0; i<object4->i_total_digit; i++)
	{
		object4->i_digit[object->i_total_digit - 1 - i] = object4->i_digit[object4->i_total_digit - 1 - i];
	}
	for (i = 0; i<object->i_total_digit - object4->i_total_digit; i++)
	{
		if (object4->d_digit[object4->d_total_digit - 1 - i] >= 0 && object4->d_digit[object4->d_total_digit - 1 - i]<10)
		{
			object4->i_digit[object->i_total_digit - object4->i_total_digit - 1 - i] = object4->d_digit[object4->d_total_digit - 1 - i];
		}
		else
		{
			object4->i_digit[object->i_total_digit - object4->i_total_digit - 1 - i] = 0;
		}
	}
	for (i = 0; i<object->i_total_digit - object4->i_total_digit; i++)
	{
		object4->d_digit[object4->d_total_digit - 1 - i] = 0;
	}
	object4->d_total_digit = object2->d_total_digit - object->i_total_digit + object2->i_total_digit;
	object4->i_total_digit = object->i_total_digit;
	for (;;)
	{
		*object5 = *object;
		if (object->d_total_digit>object4->d_total_digit)
		{
			for (i = object->d_total_digit - object4->d_total_digit; i<object->d_total_digit; i++)
			{
				object->d_digit[i] = object->d_digit[i] - object4->d_digit[i - object->d_total_digit + object4->d_total_digit];
			}
		}
		else
		{

			for (i = 0; i<object4->d_total_digit - object->d_total_digit; i++)
			{
				object->d_digit[i] = 0 - object4->d_digit[i];
			}
			for (i = object4->d_total_digit - object->d_total_digit; i<object4->d_total_digit; i++)
			{
				object->d_digit[i] = object->d_digit[i] - object4->d_digit[i - object4->d_total_digit + object->d_total_digit];
			}
			object->d_total_digit = object4->d_total_digit;
		}
		for (i = 0; i<object->d_total_digit; i++)
		{
			if (object->d_digit[i]<0 && i != object->d_total_digit - 1)
			{
				object->d_digit[i] = object->d_digit[i] + 10;
				object->d_digit[i + 1]--;
			}
			else if (object->d_digit[i]<0 && i == object->d_total_digit - 1)
			{
				object->d_digit[i] = object->d_digit[i] + 10;
				object->i_digit[0]--;
			}
		}
		for (i = 0; i<object->i_total_digit; i++)
		{
			object->i_digit[i] = object->i_digit[i] - object4->i_digit[i];
		}
		for (i = 0; i<object->i_total_digit; i++)
		{
			if (object->i_digit[i]<0 && i != object->i_total_digit - 1)
			{
				object->i_digit[i] = object->i_digit[i] + 10;
				object->i_digit[i + 1]--;
			}
			else if (object->i_digit[i]<0 && i == object->i_total_digit - 1)
			{
				if (object->i_digit[i + 1]>0 && object->i_digit[i + 1]<10)
				{
					object->i_digit[i] = object->i_digit[i] + 10;
					object->i_digit[i + 1]--;
				}
			}
		}
		c++;
		if (object->i_digit[object->i_total_digit - 1]<0)
		{
			*object = *object5;
			if (d <= object->i_total_digit - object2->i_total_digit)
			{
				object3->i_digit[object->i_total_digit - object2->i_total_digit - d] = c - 1;
				object3->i_total_digit++;
			}
			else
			{
				object3->d_digit[*d_total - d + object->i_total_digit - object2->i_total_digit] = c - 1;
				object3->d_total_digit++;
			}
			for (i = 0; i<object->i_total_digit; i++)
			{
				object->i_digit[object->i_total_digit - i] = object->i_digit[object->i_total_digit - 1 - i];
			}
			if (object->d_digit[object->d_total_digit - 1] >= 0 && object->d_digit[object->d_total_digit - 1]<10)
			{
				object->i_digit[0] = object->d_digit[object->d_total_digit - 1];
			}
			else
			{
				object->i_digit[0] = 0;
			}
			for (i = 0; i<object->d_total_digit - 1; i++)
			{
				object->d_digit[object->d_total_digit - 1 - i] = object->d_digit[object->d_total_digit - 2 - i];
			}
			object->d_digit[0] = 0;
			d++;
			c = 0;
		}
		if (d - object->i_total_digit + object2->i_total_digit>*d_total)
		{
			break;
		}
	}
	for (i = 0; i<object3->d_total_digit; i++)
	{
		if (object3->d_digit[i] == 0)
		{
			l++;
		}
		else
		{
			break;
		}
	}
	for (i = 0; i<object3->d_total_digit; i++)
	{
		object3->d_digit[i] = object3->d_digit[i + l];
	}
	object3->d_total_digit = object3->d_total_digit - l;
	l = 0;
	for (i = 0; i<object3->i_total_digit; i++)
	{
		if (object3->i_digit[object3->i_total_digit - 1 - i] == 0)
		{
			l++;
		}
		else
		{
			break;
		}
	}
	object3->i_total_digit = object3->i_total_digit - l;
	l = 0;
	object3->sign = a*b;
	*object = *object6;
	return 0;
}
void printResult(char* result)            //','찍기
{
	char* pFind = strchr(result, '.');
	printf("= ");
	if (pFind != 0)
	{
		int nLen = pFind - result;
		int nTemp = 0;
		while (*result)
		{
			if (*result == '.')
			{
				printf("%s\n", result);
				break;
			}
			if ((nLen - nTemp) % 3 == 0 && nTemp > 0)
				printf(",");
			printf("%c", *result);
			result++;
			nTemp++;
		}
	}
	else
	{
		int nLen = strlen(result);
		int nTemp = 0;
		while (*result)
		{ 
			if ((nLen - nTemp) % 3 == 0 && nTemp > 0)
				printf(",");
			printf("%c", *result);
			result++;
			nTemp++;
		}
		printf("\n");
	}
}

void main(void) { 
	printf("Start....\n");
	char exp[256];

	char pf[256];
	while (1)
	{
		printf("(input) ");
		gets(exp);
		if(strlen(exp)<1)
			continue;
		strlwr(exp);	// 대문자를 소문자로 변경
		if (is_alpha(exp))
		{
			print_var(exp);
		}
		else if (is_input(exp))
		{
			char * res = varToStr(exp);
			if (has_operator(res))
			{
				input_var_after_calc(res);
			}
			else
			{
				input_var(res);
			}
		}
		else if (strcmp(exp, "var") == 0)   
		{
			print_arrVar();
		}
		else if (strcmp(exp, "clear") == 0) 
		{
			system("clear");			 
		}
		else if (strcmp(exp, "save") == 0)  
		{
			bQuiet = 1;
			savevar();
			bQuiet = 0;
		}
		else if (strcmp(exp, "load") == 0)
		{
			bQuiet = 1;
			loadvar();
			bQuiet = 0;
		}
		else if (strcmp(exp, "end") == 0)
		{
			return;
		}
		else
		{
			if (is_legal(exp))
			{
				char * res = varToStr(exp);
				postfix(pf, res);
				char * result = calc(pf);
				printResult(result);
			}
			else
			{
				printf("= error\n");
			} 
		} 
	} 
	return ;
}
