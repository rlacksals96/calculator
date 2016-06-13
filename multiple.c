int multiple(struct BigNum *object, struct BigNum *object2, struct BigNum *object3)
{
	int i, j, k, l, m, n, o;
	int obj_num[200], obj2_num[200], obj3_num[400];
	for (i = 0; i<object->d_total_digit; i++)
	{
		obj_num[i] = object->d_digit[i];                       //  배열에 값넣어놓기
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
			l = k / 10;                                       // 합이 10이상되면 한자리 올리기위한 변수
			n = k % 10;                                      // 해당 자리에 더셈값을 위한 변수
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


