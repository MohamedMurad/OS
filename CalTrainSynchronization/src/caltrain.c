#include <pthread.h>
#include "caltrain.h"

/**
 * we divide the process of getting a passenger on a train into two stages
 * the first is leave station, the second is get on train.
 */
void leave_station(struct station *station);
void get_on_train(struct station *station);

//mutex design is used in synchronization.
pthread_mutex_t mutex;
//passengers is the currently passengers_on_station which granted a signal of a free_seat
int slected_passengers;

/**
 * initialization of mutex, passengers, and station structure
 */
void station_init(struct station *station) {
	pthread_mutex_init(&mutex, NULL);
	slected_passengers = 0;
	station->passengers_on_station = 0;
	station->num_of_free_seats = 0;
	pthread_cond_init(&station->free_seat, NULL);
	pthread_cond_init(&station->busy_seat, NULL);
}

/**
 * where count indicates how many seats are available on the train. The function must not return until
 the train is satisfactorily loaded (all passengers are in their seats, and either the train is full or all wait-
 ing passengers have boarded). Note, that the train must leave the station promptly if no passengers
 are waiting at the station or it has no available free seats.
 */
void station_load_train(struct station *station, int count) {
	station->num_of_free_seats = count;
	while (station->num_of_free_seats != 0 && station->passengers_on_station != 0) {
		pthread_cond_broadcast(&station->free_seat);
		pthread_cond_wait(&station->busy_seat, &mutex);
	}
	station->num_of_free_seats = 0;
}

/**
 *train is in the station (i.e., a call to station load train is in progress) and there are enough free seats on
 the train for this passenger to sit down. Once this function returns, the passenger robot will move the
 passenger on board the train and into a seat (you do not need to worry about how this mechanism
 works). Once the passenger is seated, it will call the function
 */
void station_wait_for_train(struct station *station) {
	pthread_mutex_lock(&mutex);
	station->passengers_on_station++;
	while (slected_passengers == station->num_of_free_seats) {
		pthread_cond_wait(&station->free_seat, &mutex);
	}
	leave_station(station);
}

/**
 * to let the train know that it’s on board.
 */
void station_on_board(struct station *station) {
	get_on_train(station);
	if (station->num_of_free_seats <= 0 || slected_passengers <= 0) {
		pthread_cond_broadcast(&station->busy_seat);
	}
	pthread_mutex_unlock(&mutex);
}

/**
 * to leave the station we increment number of passengers and decrement number of passengers_on_station
 */
void leave_station(struct station *station) {
	slected_passengers++;
	station->passengers_on_station--;
}

/**
 * to get on the train we decrement num_of_free_seats and decrement number of passengers
 */
void get_on_train(struct station *station) {
	station->num_of_free_seats--;
	slected_passengers--;
}
