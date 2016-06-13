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
			//push(i);
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
			//push(i);
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
			//i = pop();
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
				//printf("-");
				np[cnt++] = '-';
			}
			if (object[2].i_total_digit>100)
			{
				for (i = 0; i<object[2].i_total_digit - 100; i++)
				{
					//	printf("%d", object[2].i_digit_add[object[2].i_total_digit - 100 - 1 - i]);
					np[cnt++] = object[2].i_digit_add[object[2].i_total_digit - 100 - 1 - i] + 48;
				}
				for (i = 0; i<100; i++)
				{
					//printf("%d", object[2].i_digit[99 - i]);
					np[cnt++] = object[2].i_digit_add[object[2].i_total_digit - 100 - 1 - i] + 48;
				}
			}
			else
			{
				for (i = 0; i<object[2].i_total_digit; i++)
				{
					//printf("%d", object[2].i_digit[object[2].i_total_digit - i - 1]);
					np[cnt++] = object[2].i_digit[object[2].i_total_digit - i - 1] + 48;
				}
			}
			if (object[2].d_total_digit>0)
			{
				//printf(".");
				np[cnt++] = '.';
			}
			if (object[2].d_total_digit>100)
			{
				for (i = 0; i<100; i++)
				{
					//	printf("%d", object[2].d_digit[99 - i]);
					np[cnt++] = object[2].d_digit[99 - i] + 48;
				}
				for (i = 0; i<object[2].d_total_digit - 100; i++)
				{
					//printf("%d", object[2].d_digit_add[object[2].d_total_digit - 100 - 1 - i]);
					np[cnt++] = object[2].d_digit_add[object[2].d_total_digit - 100 - 1 - i] + 48;
				}
			}
			else
			{
				for (i = 0; i<object[2].d_total_digit; i++)
				{
					//printf("%d", object[2].d_digit[object[2].d_total_digit - i - 1]);
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


