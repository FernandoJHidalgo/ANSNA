#ifndef CONCEPT_H
#define CONCEPT_H

///////////////////
//  SDR Concept  //
///////////////////
//A concept named by a SDR

//References//
//-----------//
#include "FIFO.h"
#include "Table.h"

//Parameters//
//----------//
#define CONCEPT_INTERPOLATION_STRENGTH 1.0
#define CONCEPT_INTERPOLATION_INIT_STRENGTH 1.0

//Data structure//
//--------------//
typedef struct {
    Attention attention;
    Usage usage;
    /** name of the concept like in OpenNARS */
    long id; //ID assigned to the concept on conceptualization, cleaner than using its address
    SDR sdr;
    SDR_HASH_TYPE sdr_hash;
    FIFO event_beliefs;
    FIFO event_goals;
    Table precondition_beliefs;
    Table postcondition_beliefs;
    //For concept interpolation:
    double sdr_bit_counter[SDR_SIZE];
} Concept;

//Methods//
//-------//
//Assign a new name to a concept
void Concept_SetSDR(Concept *concept, SDR sdr);
//print a concept
void Concept_Print(Concept *concept);
//whether concept exists
bool Concept_Exists(Concept *concept);
//Interpolate concepts, see https://github.com/patham9/ANSNA/wiki/Concept:-Conceptual-Interpolation
void Concept_SDRInterpolation(Concept *concept, SDR *eventSDR, Truth matchTruth);

#endif
