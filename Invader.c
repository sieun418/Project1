#include "main.h"
UPOINT ptthisMypos;
int    timeflag = FALSE;
int    score,hiscore =2000, killnum;
char   *Aboom[8];
   
void main(void)
{
	srand((unsigned)time(NULL)); // 시드 초기화

	while (1)
	{
		InitConsole();   // 콘솔 초기화
		InitMyship();    // 비행기 상태 초기화
		Initenemyship(); // 적 초기화
		score = 0;
		killnum = 0;
		timeflag = FALSE;

		play();  // 1판 플레이 (죽거나 이길 때까지)

		// 게임 오버 처리
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
		printf("당신의 비행기는 파괴되었습니다.");
		ptend.y += 1;
		gotoxy(ptend);
		printf("다시 할까요? (y/n)");

		int ch;
		do {
			ch = _getch();
		} while (ch != 'y' && ch != 'n');

		if (ch == 'n') break;

		ClearScreen();  // 화면만 지우고 루프 재진입
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
		   if (ch == 224) { // 방향키 처리
			   ch = _getch();
			   switch (ch) {
			   case 75:  // ←
				   ptMyoldpos.x = ptthisMypos.x;
				   if (--ptthisMypos.x < 1) ptthisMypos.x = 1;
				   DrawMyship(&ptthisMypos, &ptMyoldpos);
				   break;
			   case 77:  // →
				   ptMyoldpos.x = ptthisMypos.x;
				   if (++ptthisMypos.x > 75) ptthisMypos.x = 75;
				   DrawMyship(&ptthisMypos, &ptMyoldpos);
				   break;
			   
			   }
		   }
		   else if (ch == ' ') {  // 스페이스바 입력 처리
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
			   myship.hp--;  // 체력 감소

			   // hp 변경 직후 바로 그려야 화면에 반영됨
			   ptMyoldpos = ptthisMypos;
			   DrawMyship(&ptthisMypos, &ptMyoldpos);

			   if (myship.hp <= 0)
			   {
				   if (score > 2000)
					   hiscore = score;
				   break; // 게임 종료
			   }
		   }
	       CheckenemyBullet(enemyship);                   
		   ptMyoldpos = ptthisMypos;               // 항상 다시 그리도록!
		   DrawMyBullet();
		   DrawMyship(&ptthisMypos, &ptMyoldpos);
		   gotoxy(ptscore);
		   
		   if(killnum < 40)
		      printf("점수 : %d",score);
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
