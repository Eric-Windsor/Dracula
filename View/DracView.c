// DracView.c ... DracView ADT implementation

#include <stdlib.h>
#include <assert.h>
#include "Globals.h"
#include "Game.h"
#include "GameView.h"
#include "DracView.h"
#include <string.h>

#define TRAIL_SECTION_LENGTH 8
#define LOCATION_ARRAY_SIZE 3
// #include "Map.h" ... if you decide to use the Map ADT
     
struct dracView {
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    GameView Game; //pls no
    int health[NUM_PLAYERS]; //been asking around and apparently this is better as an array? figured it out
    int nTraps[NUM_MAP_LOCATIONS];
    int nVamps[NUM_MAP_LOCATIONS];
    int score;
    LocationID trail[TRAIL_SIZE][NUM_PLAYERS];
    LocationID trueLocation;
};
     

// Creates a new DracView to summarise the current state of the game
DracView newDracView(char *pastPlays, PlayerMessage messages[]){
    DracView currentView = malloc(sizeof(struct dracView));
    currentView->Game = newGameView(pastPlays, messages);
        
    // Parsing pastPlays to set traps and vampires in cities
    int pastPlayLength = strlen(pastPlays);
    int index = (NUM_PLAYERS-1)*TRAIL_SECTION_LENGTH; //Index to Dracula's first play in the string
    while(index < pastPlayLength - 1) {
        char location[LOCATION_ARRAY_SIZE] = {0};
        location[0] = pastPlays[index+1];
        location[1] = pastPlays[index+2];
        location[2] = '\0';
        int locationID = abbrevToID(location);
        
        if (pastPlays[index+3] == 'T') {
            currentView->nTraps[locationID]++;
        }
        if (pastPlays[index+4] == 'V') {
            currentView->nVamps[locationID]++;
        }
        if (pastPlays[index+5] == 'M' || pastPlays[index+5] == 'V') {
            int lostCity = index - TRAIL_SIZE*NUM_PLAYERS*TRAIL_SECTION_LENGTH; // 6 rounds * 40 chars per round, to get Dracula's play that was 6 rounds ago
            char lostLocation[LOCATION_ARRAY_SIZE] = {0};
            lostLocation[0] = pastPlays[lostCity+1];
            lostLocation[1] = pastPlays[lostCity+2];
            lostLocation[2] = '\0';
            int lostLocationID = abbrevToID(lostLocation);
            
            if (pastPlays[index+5] == 'M') {
                currentView->nTraps[lostLocationID]--;
            } else if (pastPlays[index+5] == 'V') {
                currentView->nVamps[lostLocationID]--;
            }
        }
        
        index += NUM_PLAYERS*TRAIL_SECTION_LENGTH; // Distance to next Dracula play in string
    }
    
    return currentView;
}
     
     
// Frees all memory previously allocated for the DracView toBeDeleted
void disposeDracView(DracView toBeDeleted){
    //COMPLETE THIS IMPLEMENTATION
    assert(toBeDeleted != NULL);
    disposeGameView(toBeDeleted->Game);
    free( toBeDeleted );
}


//// Functions to return simple information about the current state of the game

// Get the current round
Round giveMeTheRound(DracView currentView){
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return getRound(currentView->Game); //smart
}

// Get the current score
int giveMeTheScore(DracView currentView){
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return currentView->score;
}

// Get the current health points for a given player
int howHealthyIs(DracView currentView, PlayerID player){
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return getHealth(currentView->Game, player);
    
    //return currentView->health[player]; // i see why its gotta be an array
}

// Get the current location id of a given player
LocationID whereIs(DracView currentView, PlayerID player){
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return getLocation(currentView->Game, player);
}

// Get the most recent move of a given player
void lastMove(DracView currentView, PlayerID player,
                 LocationID *start, LocationID *end){
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return;
}

// Find out what minions are placed at the specified location
void whatsThere(DracView currentView, LocationID where,
                         int *numTraps, int *numVamps){
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    *numTraps = currentView->nTraps[where];
    *numVamps = currentView->nVamps[where];
    return;
}

//// Functions that return information about the history of the game

// Fills the trail array with the location ids of the last 6 turns
void giveMeTheTrail(DracView currentView, PlayerID player,
                            LocationID trail[TRAIL_SIZE]){
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    getHistory(currentView->Game, player, trail);
    
    /*int i = 0;
    for (i = 0; i < TRAIL_SIZE; i++) {
        trail[i] = currentView->trail[i][player];
	} */
}

//// Functions that query the map to find information about connectivity

// What are my (Dracula's) possible next moves (locations)
LocationID *whereCanIgo(DracView currentView, int *numLocations, int road, int sea){
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    // call connected connections
    return connectedLocations(currentView->Game, numLocations, currentView->trueLocation, 
    	PLAYER_DRACULA, getRound(currentView->Game), road, FALSE, sea);
}

// What are the specified player's next possible moves
LocationID *whereCanTheyGo(DracView currentView, int *numLocations,
                           PlayerID player, int road, int rail, int sea){
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    //call connected locations
    return connectedLocations(currentView->Game, numLocations, getLocation(currentView->Game, player),
    	player,getRound(currentView->Game), road, rail, sea);
}
