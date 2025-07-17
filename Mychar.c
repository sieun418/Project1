#include "main.h"

MYSHIP  myship;
BULLET myship_bullet[MAXMY_BULLET];

int myship_hp = 3;
char* myship_shape[] = {
	"-i^i-",  // HP 3
	"i^i-",   // HP 2
	"i^i",    // HP 1
};


void InitMyship()
{
	myship.flag = TRUE;
	myship.pos.x = MYSHIP_BASE_POSX;
	myship.pos.y = MYSHIP_BASE_POSY;
	myship.hp = 3; //  체력 초기화
}



void DrawMyship(UPOINT* pt, UPOINT* oldpt)
{
	gotoxy(*oldpt);
	printf("      ");
	gotoxy(*pt);
	int index = 3 - myship.hp;
	if (index < 0) index = 0;
	if (index > 2) index = 2;
	printf("%s", myship_shape[index]);
}



void DrawMyBullet()
{
	int i;
	UPOINT ptpos, oldpos;

	for (i = 0; i < MAXMY_BULLET; i++)
	{
		if (myship_bullet[i].flag == TRUE)
		{
			if (myship_bullet[i].pos.y < 1)
			{
				myship_bullet[i].flag = FALSE;
				oldpos.x = myship_bullet[i].pos.x;
				oldpos.y = myship_bullet[i].pos.y;
				gotoxy(oldpos);
				printf(" ");
				continue;
			}

			oldpos.x = myship_bullet[i].pos.x;
			oldpos.y = myship_bullet[i].pos.y;
			--myship_bullet[i].pos.y;
			ptpos.x = myship_bullet[i].pos.x;
			ptpos.y = myship_bullet[i].pos.y;
			gotoxy(oldpos);
			printf(" ");
			gotoxy(ptpos);
			printf("!");
		}
	}
}

void MyBulletshot(UPOINT ptthisMypos)
{
	int i;
	for (i = 0; i < MAXMY_BULLET; i++)
	{
		if (myship_bullet[i].flag == FALSE)
		{
			myship_bullet[i].flag = TRUE;
			myship_bullet[i].pos.x = ptthisMypos.x + 2;
			myship_bullet[i].pos.y = ptthisMypos.y - 1;
			break;
		}
	}
}

int CheckMybullet(UPOINT ptthisMypos)
{
	int i, flag = FALSE;
	for (i = 0; i < MAXENEMY_BULLET; i++)
	{
		if (enemy_bullet[i].flag == TRUE)
		{
			if (ptthisMypos.x <= enemy_bullet[i].pos.x &&
				enemy_bullet[i].pos.x <= ptthisMypos.x + 4 &&
				enemy_bullet[i].pos.y == ptthisMypos.y)
			{
				flag = TRUE;
				break;
			}
		}
	}
	return flag ? 0 : 1;
}

	

