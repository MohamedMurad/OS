#include <pthread.h>

struct station {
    int passengers_on_station;
    int num_of_free_seats;
    pthread_cond_t free_seat, busy_seat;
};

void station_init(struct station *station);

void station_load_train(struct station *station, int count);

void station_wait_for_train(struct station *station);

void station_on_board(struct station *station);
