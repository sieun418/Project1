#include "main.h"
UPOINT ptthisMypos;
int    timeflag = FALSE;
int    score,hiscore =2000, killnum;
char   *Aboom[8];
   
void main(void)
{
	srand((unsigned)time(NULL)); // �õ� �ʱ�ȭ

	while (1)
	{
		InitConsole();   // �ܼ� �ʱ�ȭ
		InitMyship();    // ����� ���� �ʱ�ȭ
		Initenemyship(); // �� �ʱ�ȭ
		score = 0;
		killnum = 0;
		timeflag = FALSE;

		play();  // 1�� �÷��� (�װų� �̱� ������)

		// ���� ���� ó��
		UPOINT ptend = { 36, 12 };
		char* Aboom[8] = {
			"i<^>i", "i(*)i", "(* *)", "(** **)", " (* *) ", "  (*)  ", "   *   ", "       "
		};
		DWORD bcount = GetTickCount();
		for (int bp = 0; bp < 8; )
		{
			if (GetTickCount() - bcount > 100)
			{
				gotoxy(ptthisMypos);
				printf("%s", Aboom[bp++]);
				bcount = GetTickCount();
			}
		}

		gotoxy(ptend);
		printf("����� ������ �ı��Ǿ����ϴ�.");
		ptend.y += 1;
		gotoxy(ptend);
		printf("�ٽ� �ұ��? (y/n)");

		int ch;
		do {
			ch = _getch();
		} while (ch != 'y' && ch != 'n');

		if (ch == 'n') break;

		ClearScreen();  // ȭ�鸸 ����� ���� ������
	}
}

void  play()
{
	static UPOINT ptMyoldpos;
	DWORD         gthisTickCount = GetTickCount();
    DWORD         gCount = gthisTickCount;
	DWORD         Count = gthisTickCount;
	DWORD         bulletcount = gthisTickCount;
	UPOINT        ptscore,pthi;
	int           juckspeed=500;

	InitConsole();      
	Initenemyship();  
	
	ptthisMypos.x = ptMyoldpos.x = MYSHIP_BASE_POSX;
    ptthisMypos.y = ptMyoldpos.y = MYSHIP_BASE_POSY;
	
	ptscore.x = 68;
	ptscore.y = 1;

	pthi.x =  2;
	pthi.y =  1;
	
	
	while(TRUE)
	{
	   gthisTickCount = GetTickCount();
	
	   if (_kbhit()) {
		   int ch = _getch();
		   if (ch == 224) { // ����Ű ó��
			   ch = _getch();
			   switch (ch) {
			   case 75:  // ��
				   ptMyoldpos.x = ptthisMypos.x;
				   if (--ptthisMypos.x < 1) ptthisMypos.x = 1;
				   DrawMyship(&ptthisMypos, &ptMyoldpos);
				   break;
			   case 77:  // ��
				   ptMyoldpos.x = ptthisMypos.x;
				   if (++ptthisMypos.x > 75) ptthisMypos.x = 75;
				   DrawMyship(&ptthisMypos, &ptMyoldpos);
				   break;
			   
			   }
		   }
		   else if (ch == ' ') {  // �����̽��� �Է� ó��
			   if (gthisTickCount - bulletcount > 500) {
				   MyBulletshot(ptthisMypos);
				   bulletcount = gthisTickCount;
			   }
		   }
	   }

  
	   if( gthisTickCount - Count > 150)
	   {
	
		   if (CheckMybullet(ptthisMypos) == 0)
		   {
			   myship.hp--;  // ü�� ����

			   // hp ���� ���� �ٷ� �׷��� ȭ�鿡 �ݿ���
			   ptMyoldpos = ptthisMypos;
			   DrawMyship(&ptthisMypos, &ptMyoldpos);

			   if (myship.hp <= 0)
			   {
				   if (score > 2000)
					   hiscore = score;
				   break; // ���� ����
			   }
		   }
	       CheckenemyBullet(enemyship);                   
		   ptMyoldpos = ptthisMypos;               // �׻� �ٽ� �׸�����!
		   DrawMyBullet();
		   DrawMyship(&ptthisMypos, &ptMyoldpos);
		   gotoxy(ptscore);
		   
		   if(killnum < 40)
		      printf("���� : %d",score);
		   else
		   {
			   timeflag = TRUE;
			   break;
		   }

		   if(killnum > 20)                               
			   juckspeed = 150;                           
		   
		   gotoxy(pthi);
		   
	   	   Count = gthisTickCount;
	   }
	   
	   if( gthisTickCount - gCount > juckspeed)
	   {
		   Bulletshot();                                  
	       DrawBullet();                                  
	  	   CalenemyshipPos();                             
		   Drawenemyship();                               
		   if(Checkenemypos() == 1)
			   break;                
		   gCount = gthisTickCount;                       
	   }
	}

}
