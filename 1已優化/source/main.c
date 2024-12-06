#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// ���B���i�ק�A���i�H�ק�optimization_shuffle();�Poptimization_deal();���ѼƩw�q
void shuffle(int wDeck[][13]);
void deal(const int wDeck[][13], const char* wFace[], const char* wSuit[]);
void optimization_shuffle(int wDeck[][13]);
void optimization_deal(const int wDeck[][13], const char* wFace[], const char* wSuit[]);
double get_high_resolution_time();

// ���B���i�ק�
static int shuffle_count = 0;
static int deal_count = 0;
static int opt_shuffle_count = 0;
static int opt_deal_count = 0;

// �ɶ����q���
double get_high_resolution_time() {
    LARGE_INTEGER frequency;
    LARGE_INTEGER count;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&count);
    return (double)count.QuadPart / (double)frequency.QuadPart;
}

// �įണ�ɭp����
double calculate_improvement(double original, double optimized) {
    return ((original - optimized) / original) * 100.0;
}

// ��l�~�P (shuffle) ���
void shuffle(int wDeck[][13]) {
    shuffle_count = 0;
    int row, column, card;

    for (card = 1; card <= 52; card++) {
        do {
            row = rand() % 4;
            column = rand() % 13;
            shuffle_count++;
        } while (wDeck[row][column] != 0);

        wDeck[row][column] = card;
    }
}

// ��l�o�P (deal) ���
void deal(const int wDeck[][13], const char* wFace[], const char* wSuit[]) {
    deal_count = 0;
    int card, row, column;

    for (card = 1; card <= 52; card++) {
        for (row = 0; row <= 3; row++) {
            for (column = 0; column <= 12; column++) {
                deal_count++;
                if (wDeck[row][column] == card) {
                    printf("%5sof%-8s%c", wFace[column], wSuit[row],
                        card % 2 == 0 ? '\n' : '\t');
                }
            }
        }
    }
    printf("\n");
}

// �u�ƫ�~�P (optimization_shuffle) ���
void optimization_shuffle(int wDeck[][13]) {
    opt_shuffle_count = 0;
    int cards[52];
    for (int i = 0; i < 52; i++) {
        cards[i] = i + 1;
    }

    for (int i = 51; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = cards[i];
        cards[i] = cards[j];
        cards[j] = temp;
        opt_shuffle_count++;
    }

    for (int i = 0; i < 52; i++) {
        wDeck[i / 13][i % 13] = cards[i];
    }
}

// �i�@�B�u�ƫ᪺�o�P (optimization_deal) ���
void optimization_deal(const int wDeck[][13], const char* wFace[], const char* wSuit[]) {
    opt_deal_count = 0;

    char output_buffer[5000]; // �w����X�r��j�p
    int buffer_index = 0;

    for (int card = 0; card < 52; card++) {
        opt_deal_count++;
        int row = card / 13;
        int column = card % 13;

        buffer_index += sprintf(&output_buffer[buffer_index], "%5sof%-8s%c",
            wFace[column], wSuit[row], (card + 1) % 2 == 0 ? '\n' : '\t');
    }

    printf("%s", output_buffer); // �@���ʿ�X�Ҧ����G
}






// �D���
int main(void) {
    const char* suit[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };
    const char* face[13] = {
        "Ace", "Deuce", "Three", "Four",
        "Five", "Six", "Seven", "Eight",
        "Nine", "Ten", "Jack", "Queen", "King"
    };
    int deck[4][13] = { 0 };
    double start_time, end_time;

    srand((unsigned int)time(0));

    // �����l shuffle �ðO���ɶ�
    start_time = get_high_resolution_time();
    shuffle(deck);
    end_time = get_high_resolution_time();
    double shuffle_time = (end_time - start_time) * 1000000.0;

    // �����u�ƫ� shuffle �ðO���ɶ�
    start_time = get_high_resolution_time();
    optimization_shuffle(deck);
    end_time = get_high_resolution_time();
    double optimized_shuffle_time = (end_time - start_time) * 1000000.0;

    // �����l deal �ðO���ɶ�
    start_time = get_high_resolution_time();
    deal(deck, face, suit);
    end_time = get_high_resolution_time();
    double deal_time = (end_time - start_time) * 1000000.0;

    // �����u�ƫ� deal �ðO���ɶ�
    start_time = get_high_resolution_time();
    optimization_deal(deck, face, suit);
    end_time = get_high_resolution_time();
    double optimized_deal_time = (end_time - start_time) * 1000000.0;

    // �p��įണ�ɦʤ���
    double shuffle_improvement = calculate_improvement(shuffle_time, optimized_shuffle_time);
    double deal_improvement = calculate_improvement(deal_time, optimized_deal_time);

    // ���L���G
    printf("��l�~�P����ɶ�: %.4f microseconds\n", shuffle_time);
    printf("��l�~�P���榸��: %d\n", shuffle_count);
    printf("�u�Ƭ~�P����ɶ�: %.4f microseconds\n", optimized_shuffle_time);
    printf("�u�Ƭ~�P���榸��: %d\n", opt_shuffle_count);
    printf("�~�P�įണ��: %.4f%%\n\n", shuffle_improvement);

    printf("��l�o�P����ɶ�: %.4f microseconds\n", deal_time);
    printf("��l�o�P���榸��: %d\n", deal_count);
    printf("�u�Ƶo�P����ɶ�: %.4f microseconds\n", optimized_deal_time);
    printf("�u�Ƶo�P���榸��: %d\n", opt_deal_count);
    printf("�o�P�įണ��: %.4f%%\n", deal_improvement);

    return 0;
}




