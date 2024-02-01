#include <stdio.h>
#include <stdlib.h>
#include <time.h>
char *display(int card) {
  char *temp_card = malloc(3 * sizeof(char));
  temp_card[1] = '\0';
  temp_card[2] = '\0';
  if (card == 11) {
    temp_card[0] = 'J';
  }
  if (card == 12) {
    temp_card[0] = 'Q';
  }
  if (card == 13) {
    temp_card[0] = 'K';
  }
  if (card == 1) {
    temp_card[0] = 'A';
  }
  if (card >= 2 && card < 10) {
    temp_card[0] = (char)(card + 48);
  } else if (card == 10) {
    temp_card[0] = '1';
    temp_card[1] = '0';
  }

  return temp_card;
}
int playgame(int betPoint, int card1, int card2, int Points) {
  int card3, sum;
   card3 = rand() % 13 + 1;
  sum = card1 + card2 + card3;
 
  printf("Your third card is %s\n", display(card3));
  printf("So your sum is: %d\n", sum);
  if (sum > 21) {
    Points = Points - betPoint;
    printf("You lose %d points\n", betPoint);
    printf("Your remaining points: %d \n\n", Points);
  } else {
    Points = Points + betPoint;
    printf("You won %d points\n", betPoint);
    printf("Your remaining points: %d \n\n", Points);
  }

  return Points;
}

int main() {
  int points = 100;
  int betPoint, card1, card2;
  char tempCard1, tempCard2;
  srand(time(NULL));
  printf("You have 100 points in your account\n");
  while (points > 0) {
    card1 = rand() % 13 + 1;
    card2 = rand() % 13 + 1;

    printf("Your cards are %s and %s \n", display(card1), display(card2));
    printf("How many points you want to bet?\n");
    scanf("%d", &betPoint);
    if (betPoint <= points&& betPoint>0) {
      points = playgame(betPoint, card1, card2, points);
    } 
    else if(betPoint<=0)
    {
      printf("Betpoint cannot be negative or zero\n");
    }
    else {
      printf("You don't have enough points\n");
    }
  }
  printf("Game over!!!");
  return 0;
}