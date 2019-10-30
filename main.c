#define colorWhite 0xffffff
#define colorWhite 0xffffff
#define colorPurpleDark 0x000030
#define colorPurpleLight 0x000099
#define colorGreenLight 0x1fcecb
#define colorYellow 0xaaff00
#define colorRed 0xff8800

void putString(char *c, int size, int color, int x, int y, int d);
void putChar(char c, int size, int color, int x, int y, int d);
void printAllLetters();
void drawRect(int positionX, int positionY, int sizeX, int sizeY, int color);
void drawHorizontalLine(int positionX, int positionY, int sizeX, int color);
void drawVerticalalLine(int positionX, int positionY, int sizeY, int color);
void clearSreen(int color, int d);
void delay(int d);
void drawSquare(int positionX, int positionY, int size, int color);
void setPixel(int x, int y, int color);
void showSplashScreen();
void showGradientScreen();
void clearPercent();
void intToChar(int num, char *c, int lenth);
void showMenu();
int getKey();
void kbReset(int code);
void showCalculator();
void showExit();
void floatToChar(float num, char *c);
void printNumber(int num);

/*************************************************************
cd "C:\Program Files\qemu"
java -jar builderFont.jar C:\Users\leogr\Desktop\система\MYOS
*************************************************************/

int start()
{
	// showSplashScreen();
	// showMenu();
	showCalculator();
	
	// printKeyCode();
	while (1)
		;
}

void floatToChar(float num, char *c)
{ //c[15] = 8x.6x
	int intNum = num;
	for (int i = 7; i >= 0; i--)
	{
		c[i] = intNum % 10 + '0';
		intNum /= 10;
	}
	c[8] = '.';
	for (int i = 9; i < 15; i++)
	{
		num *= 10;
		c[i] = (int)num % 10 + '0';
	}
}
void printKeyCode() {
	while (getKey() == 0 || getKey() == 250);
	char c[10];
	intToChar(getKey(), c, 10);
	putString(c, 10, colorWhite, 0, 0, 0);
}
void showMenu()
{
	clearSreen(0x000055, 0);
	char menuStr[] = "Menu";
	char calcStr[] = "Calculator";
	char exitStr[] = "Exit";

	putString(menuStr, 5, colorWhite, 420, 250, 0);
	putString(calcStr, 3, colorYellow, 380, 400, 0);
	putString(exitStr, 3, colorWhite, 450, 450, 0);

	int selected = 1;
	int keyCode = 0;
	while (1)
	{
		while (keyCode == 0)
			keyCode = getKey();

		if (keyCode == 0x48 && selected > 1)
		{ //up
			putString(calcStr, 3, colorYellow, 380, 400, 0);
			putString(exitStr, 3, colorWhite, 450, 450, 0);
			selected = 1;
		}
		else if (keyCode == 0x50 && selected < 2)
		{ //down
			putString(calcStr, 3, colorWhite, 380, 400, 0);
			putString(exitStr, 3, colorYellow, 450, 450, 0);
			selected = 2;
		}
		else if (keyCode == 0x1c)
		{ //enter
			if (selected == 1)
				showCalculator();
			else if (selected == 2)
				showExit();
		}

		kbReset(keyCode);
		keyCode = 0;
	}
}
void showCalculator()
{
	clearSreen(0x000000, 10000);

	int num1 = 0;
	int num2 = 0;
	int operationCode = 0;
	int keyCode = 0;

	printNumber(0);
	while (1)
	{
		while (keyCode == 0)
			keyCode = getKey();

		if (keyCode == 0x52)
			increaseNum(0, &num1, &num2, operationCode);
		else if (keyCode == 0x4f)
			increaseNum(1, &num1, &num2, operationCode);
		else if (keyCode == 0x50)
			increaseNum(2, &num1, &num2, operationCode);
		else if (keyCode == 0x51)
			increaseNum(3, &num1, &num2, operationCode);
		else if (keyCode == 0x4b)
			increaseNum(4, &num1, &num2, operationCode);
		else if (keyCode == 0x4c)
			increaseNum(5, &num1, &num2, operationCode);
		else if (keyCode == 0x4d)
			increaseNum(6, &num1, &num2, operationCode);
		else if (keyCode == 0x47)
			increaseNum(7, &num1, &num2, operationCode);
		else if (keyCode == 0x48)
			increaseNum(8, &num1, &num2, operationCode);
		else if (keyCode == 0x49)
			increaseNum(9, &num1, &num2, operationCode);
		else if (keyCode == 0x35 || // /
				 keyCode == 0x37 || // *
				 keyCode == 0x4a || // -
				 keyCode == 0x4e)   // +
		{
			operationCode = keyCode;
			printOperation(operationCode);
		}
		else if (keyCode == 0xe) // <-
		{
			if (operationCode == 0)
				printNumber(num1 /= 10);
			else
				printNumber(num2 /= 10);
		}
		else if (keyCode == 0x1c) //enter
		{
			if (operationCode == 0x35)
				printNumber(num1 /= num2);
			else if (operationCode == 0x37)
				printNumber(num1 *= num2);
			else if (operationCode == 0x4a)
				printNumber(num1 -= num2);
			else if (operationCode == 0x4e)
				printNumber(num1 += num2);
			
			operationCode = 0;
			num2 = 0;
		}
		else if (keyCode == 0x1)
			return;
		
		delay(10000000);

		kbReset(keyCode);
		keyCode = 0;
	}
}
void increaseNum(int n, int *num1, int *num2, int operationCode)
{
	if (operationCode == 0)
	{
		*num1 = *num1 * 10 + n;
		printNumber(*num1);
	}
	else
	{
		*num2 = *num2 * 10 + n;
		printNumber(*num2);
	}
}
void printOperation(int keyCode)
{
	if (keyCode == 0x35)
		putChar('/', 5, colorWhite, 0, 0, 0);
	else if (keyCode == 0x37)
		putChar('*', 5, colorWhite, 0, 0, 0);
	else if (keyCode == 0x4a)
		putChar('-', 5, colorWhite, 0, 0, 0);
	else if (keyCode == 0x4e)
		putChar('+', 5, colorWhite, 0, 0, 0);
}
void printNumber(int num)
{
	char str[12];
	intToChar(num, str, 12);
	drawRect(130, 290, 500, 50, colorWhite);
	// clearSreen(colorWhite, 0);
	putString(str, 3, 0, 200, 300, 0);
}
void showExit()
{
	clearSreen(colorWhite, 10000);
}
int getKey()
{
	asm("mov eax, 0");
	asm("in al, 0x60");
}
void kbReset(int code)
{
	asm("mov eax, 0");
	asm("mov al, [ebp-4]");
	asm("out 0x64, al");
}
void putString(char *c, int size, int color, int x, int y, int d)
{
	int bias = 0;
	while (*c)
	{
		putChar(*c, size, color, x + bias, y, d);
		bias += 8 * size;
		c++;
	}
}
void putChar(char c, int size, int color, int x, int y, int d)
{
	char *p = 0x8004 + (c - 32) * 64;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (*p != 0)
				drawSquare(j * size + x, i * size + y, size, color);
			delay(d);
			p++;
		}
	}
}
void printAllLetters()
{
	char *p = 0x8004;
	int biasX = 0;
	int biasY = 0;
	for (int l = 0; l < 90; l++)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (*p != 0)
				{
					drawSquare((j + biasX) * 4, (i + biasY) * 4, 4, colorWhite);
				}
				p++;
			}
		}
		biasX += 10;
		if (biasX > 240)
		{
			biasY += 20;
			biasX = 0;
		}
	}
}
void drawRect(int positionX, int positionY, int sizeX, int sizeY, int color)
{
	for (int x = positionX; x < positionX + sizeX; x++)
		for (int y = positionY; y < positionY + sizeY; y++)
			setPixel(x, y, color);
}
void drawHorizontalLine(int positionX, int positionY, int sizeX, int color)
{
	for (int x = positionX; x < positionX + sizeX; x++)
		setPixel(x, positionY, color);
}
void drawVerticalalLine(int positionX, int positionY, int sizeY, int color)
{
	for (int y = positionY; y < positionY + sizeY; y++)
		setPixel(positionX, y, color);
}
void clearSreen(int color, int d)
{
	for (int y = 0; y < 768; y++)
	{
		for (int x = 0; x < 1024; x++)
			setPixel(x, y, color);
		delay(d);
	}
}
void delay(int d)
{
	for (int i = 0; i < d; i++)
		;
}
void drawSquare(int positionX, int positionY, int size, int color)
{
	for (int x = positionX; x < positionX + size; x++)
	{
		for (int y = positionY; y < positionY + size; y++)
		{
			setPixel(x, y, color);
		}
	}
}
void setPixel(int x, int y, int color)
{
	int *p = 0x8000;
	char *c = *p;
	c += ((y * 1024) + x) * 3;
	*(int *)c = color;
}
void showSplashScreen()
{
	showGradientScreen();
	char loading[] = "Loading ...";
	char percent[3];
	char percentLetter[] = "%";
	int colorLoading;

	putString(percentLetter, 5, colorGreenLight, 510, 450, 0);

	for (int num1 = 3; num1 < 100; num1 += 4)
	{
		clearPercent();
		intToChar(num1, percent, 3);
		putString(percent, 5, colorGreenLight, 430, 450, 0);
		if (num1 % 3 == 0)
			putString(loading, 5, colorYellow, 300, 350, 100000);
		else
			putString(loading, 5, colorRed, 300, 350, 100000);
	}

	clearSreen(colorPurpleDark, 100000);
}
void showGradientScreen()
{
	int color = 0x000022;
	for (int y = 0; y < 768; y++)
	{
		for (int x = 0; x < 1024; x++)
		{
			setPixel(x, y, color);
		}
		if (y < 384)
		{
			if (y % 5 == 0)
				color += 0x010000;
		}
		else
		{
			if (y % 5 == 0)
				color -= 0x010000;
		}
	}
}
void clearPercent()
{
	int color = 0x000022;
	for (int y = 0; y < 768; y++)
	{
		for (int x = 430; x <= 510; x++)
		{
			if (y >= 450 && y <= 490)
			{
				setPixel(x, y, color);
			}
		}
		if (y < 384)
		{
			if (y % 5 == 0)
				color += 0x010000;
		}
		else
		{
			if (y % 5 == 0)
				color -= 0x010000;
		}
	}
}
void intToChar(int num, char *c, int lenth)
{
	int numCopy = num;
	if (num < 0)
		num *= -1;
	for (int i = lenth - 2; i >= 0; i--)
	{
		c[i] = num % 10 + '0';
		if (num == 0)
			c[i] = ' ';
		num /= 10;
	}
	if(numCopy < 0)
		c[0] = '-';
}