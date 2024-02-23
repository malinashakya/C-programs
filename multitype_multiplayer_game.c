#include <stdlib.h>
#include <string.h>
#include <time.h>

struct GameRecord {
  int card1;
  int card2;
  int card3;
  int betPoint;
  int result;
  int balance;
};

struct GameType {
  int (*conditionss)(int, int, int);
  int (*sumvalue)(int, int, int);
};
struct Player {
  char *name;
};

struct Player newPlayer(char *name) {
  struct Player player;
  player.name = malloc(strlen(name) + 1);
  strcpy(player.name, name);
  return player;
}
char *display(int card) {
  char *temp_card = malloc(3 * sizeof(char));
  temp_card[1] = '\0';
  temp_card[2] = '\0';
  if (card == 11) {
    temp_card[0] = 'J';
  } else if (card == 12) {
    temp_card[0] = 'Q';
  } else if (card == 13) {
    temp_card[0] = 'K';
  } else if (card == 1) {
    temp_card[0] = 'A';
  } else if (card >= 2 && card < 10) {
    temp_card[0] = (char)(card + 48);
  } else if (card == 10) {
    temp_card[0] = '1';
    temp_card[1] = '0';
  }
  return temp_card;
}

int sumIsLessThan21(int card1, int card2, int card3) {
  return (card1 + card2 + card3) < 21;
}

int sumIsLessThan17(int card1, int card2, int card3) {
  return (card1 + card2 + card3) < 17;
}

int AJQKare10(int card1, int card2, int card3) {
  if (card1 > 10 || card1 == 10) {
    card1 = 10;
  }
  if (card2 > 10 || card2 == 10) {
    card2 = 10;
  }
  if (card3 > 10 || card3 == 10) {
    card3 = 10;
  }
  return (card1 + card2 + card3) < 21;
}

int JQKare10(int card1, int card2, int card3) {
  if (card1 > 10) {
    card1 = 10;
  }
  if (card2 > 10) {
    card2 = 10;
  }
  if (card3 > 10) {
    card3 = 10;
  }
  return (card1 + card2 + card3) < 21;
}

int sumvalueAJQKare10(int card1, int card2, int card3) {
  if (card1 > 10 || card1 == 10) {
    card1 = 10;
  }
  if (card2 > 10 || card2 == 10) {
    card2 = 10;
  }
  if (card3 > 10 || card3 == 10) {
    card3 = 10;
  }
  return (card1 + card2 + card3);
}

int sumvalueJQKare10(int card1, int card2, int card3) {
  if (card1 > 10) {
    card1 = 10;
  }
  if (card2 > 10) {
    card2 = 10;
  }
  if (card3 > 10) {
    card3 = 10;
  }
  return (card1 + card2 + card3);
}

int normalsum(int card1, int card2, int card3) {
  return (card1 + card2 + card3);
}

int playgame(int betPoint, int card1, int card2, int *Points,
             struct GameRecord *records, int round, struct GameType gametype) {
  int card3, sum;
  card3 = rand() % 13 + 1;

  sum = gametype.sumvalue(card1, card2, card3);

  records[round].card1 = card1;
  records[round].card2 = card2;
  records[round].card3 = card3;
  records[round].betPoint = betPoint;

  printf("Your third card is %s\n", display(card3));
  printf("So your sum is: %d\n", sum);

  if (gametype.conditionss(card1, card2, card3) == 0) {
    *Points = *Points - betPoint;
    records[round].result = -betPoint;
    printf("You lose %d points\n", betPoint);
    printf("Your remaining points: %d \n\n", *Points);
  } else {
    *Points = *Points + betPoint;
    records[round].result = betPoint;
    printf("You won %d points\n", betPoint);
    printf("Your remaining points: %d \n\n", *Points);
  }
  records[round].balance = *Points;
  return *Points;
}

void displayHistory(struct GameRecord *records, int rounds,
                    struct Player *Player, int numPlayers) {
  printf("\nGame History:\n");
  int j = 0, count = 0;
  for (int i = 0; i < rounds; i++) {
    if (j > numPlayers - 1) {
      j = 0;
    }
    if (j == 0) {
      count++;
    }
    if (records[j].balance == 0) {
      printf("Player %s is out of the game\n", Player[j].name);
    } else {
      printf("Player %s - Round %d: Cards %s, %s, %s | Bet: %d | Result: %d | "
             "Balance: %d\n",
             Player[j].name, count, display(records[i].card1),
             display(records[i].card2), display(records[i].card3),
             records[i].betPoint, records[i].result, records[i].balance);
    }
    j++;
  }
}

struct GameRecord *Reallocation(struct GameRecord *records, int rounds) {
  struct GameRecord *new_records =
      (struct GameRecord *)malloc(sizeof(struct GameRecord) * (rounds + 1));

  memcpy(new_records, records, sizeof(struct GameRecord) * rounds);
  if (rounds > 0) {
    free(records);
  }
  return new_records;
}

struct GameType createsumIsLessThan21() {
  struct GameType gametype;
  gametype.conditionss = sumIsLessThan21;
  gametype.sumvalue = normalsum;
  printf("You have selected the Win if sum is less than 21 condition\n");
  return gametype;
}

struct GameType createsumIsLessThan17() {
  struct GameType gametype;
  gametype.conditionss = sumIsLessThan17;
  gametype.sumvalue = normalsum;
  printf("You have selected the Win if sum is less than 17 condition\n");
  return gametype;
}

struct GameType createAJQKare10() {
  struct GameType gametype;
  gametype.conditionss = AJQKare10;
  gametype.sumvalue = sumvalueAJQKare10;
  printf("You have selected the Win if A, J, K, Q are equal to 10\n");
  return gametype;
}

struct GameType createJQKare10() {
  struct GameType gametype;
  gametype.conditionss = JQKare10;
  gametype.sumvalue = sumvalueJQKare10;
  printf("You have selected the Win if J, K, Q are equal to 10, A is equal to "
         "1\n");
  return gametype;
}

int main() {
  printf("Welcome to the game of Blackjack!\n");
  int condition;
  int (*conditionss)(int, int, int);
  int (*sumvalue)(int, int, int);
  printf("Select the game condition:\n");
  printf("1. Win if sum is less than 21\n");
  printf("2. Win if sum is less than 17\n");
  printf("3. Win if J, K, Q, A and sum is less than 21\n");
  printf("4. Win if J, K, Q are equal to 10, A is equal to 1 and sum is less "
         "than 21\n");
  scanf("%d", &condition);

  int numPlayers;
  printf("Enter the number of players (1-17): ");
  scanf("%d", &numPlayers);

  if (numPlayers < 1 || numPlayers > 17) {
    printf("Invalid number of players. Exiting...\n");
    return 1;
  }

  struct Player Players[numPlayers];
  for (int i = 0; i < numPlayers; i++) {
    char playerName[20];
    printf("Enter name of Player %d: ", i + 1);
    scanf("%s", playerName);
    Players[i] = newPlayer(playerName);
  }

  printf("Names of players:\n");
  for (int i = 0; i < numPlayers; i++) {
    printf("Player %d: %s\n", i + 1, Players[i].name);
  }

  int startingPoints = 100;
  int betPoint, card1, card2, rounds = 0;
  struct GameRecord *records = NULL;

  srand(time(NULL));

  // Array to store player balances
  int playerBalances[numPlayers];
  for (int i = 0; i < numPlayers; i++) {
    playerBalances[i] = startingPoints;
  }

  printf("\nYou each have 100 points in your accounts.\n");

  struct GameType gametype;

  // Main game loop
  while (1) {
    // Loop through each player
    for (int player = 0; player < numPlayers; player++) {
      if (playerBalances[player] <= 0) {
        printf("Player %s is out of the game.\n", Players[player].name);
        continue;
      }

      card1 = rand() % 13 + 1;
      card2 = rand() % 13 + 1;
      if (condition == 1) {
        gametype = createsumIsLessThan21();
      } else if (condition == 2) {
        gametype = createsumIsLessThan17();
      } else if (condition == 3) {
        gametype = createAJQKare10();
      } else if (condition == 4) {
        gametype = createJQKare10();
      } else {
        printf("Wrong selection of game");
      }
      printf("\nPlayer %s, your cards are %s and %s \n", Players[player].name,
             display(card1), display(card2));
      printf("How many points do you want to bet?\n");

      scanf("%d", &betPoint);
      if (betPoint > 0 && betPoint <= playerBalances[player]) {
        records = Reallocation(records, rounds);
        playerBalances[player] =
            playgame(betPoint, card1, card2, &playerBalances[player], records,
                     rounds, gametype);
        rounds++;
      } else if (betPoint <= 0) {
        printf("Bet point cannot be negative or zero\n");
      } else {
        printf("Player %s, you don't have enough points\n",
               Players[player].name);
      }
    }

    printf("\nDo you want to continue to the next round? (y/n): ");
    char response;
    scanf("\n%c", &response);
    if (response == 'n') {
      break; // Exit the game if the user does not want to continue
    } else if (response != 'y') {
      printf("Wrong input\n");
      printf("\nDo you want to continue to the next round? (y/n): ");
      char response;
      scanf("\n%c", &response);
    }
  }

  displayHistory(records, rounds, Players, numPlayers);

  free(records);

  printf("Game over!!!\n");
  return 0;
}