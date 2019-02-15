#include "ANSNA.h"


long currentTime = CONCEPT_LATENCY_PERIOD+1;
void ANSNA_INIT()
{
    SDR_INIT();
    Memory_INIT(); //clear data structures
    Event_INIT(); //reset base id counter
    currentTime = CONCEPT_LATENCY_PERIOD+1; //reset time
    event_inspector = NULL;
}

void ANSNA_Cycles(int cycles)
{
    for(int i=0; i<cycles; i++)
    {
        IN_DEBUG( printf("\nNew inference cycle:\n----------\n"); )
        cycle(currentTime);
        currentTime++;
    }
}

Event ANSNA_AddInput(SDR sdr, char type, Truth truth)
{
    Event ev = Event_InputEvent(sdr, type, truth, currentTime);
    Memory_addEvent(&ev);
    IN_OUTPUT( printf("INPUT EVENT"); Event_Print(&ev); )
    return ev;
}

Event ANSNA_AddInputBelief(SDR sdr)
{
    return ANSNA_AddInput(sdr, EVENT_TYPE_BELIEF, ANSNA_DEFAULT_TRUTH);
}

Event ANSNA_AddInputGoal(SDR sdr)
{
    return ANSNA_AddInput(sdr, EVENT_TYPE_GOAL, ANSNA_DEFAULT_TRUTH);
}

void ANSNA_AddOperation(SDR sdr, Action procedure)
{
    Memory_addOperation((Operation) {.sdr = sdr, .action = procedure});
}

void ANSNA_Util_PrintExistingEventNarsese(Event e)
{
    int closest_concept_i=0;
    if(Memory_getClosestConcept(&e, &closest_concept_i))
    {
        Concept *c = concepts.items[closest_concept_i].address;
        char* st = e.type == EVENT_TYPE_BELIEF ? "." : "!";
        printf("Input: %ld%s %%%f;%f%%\n", c->id, st, e.truth.frequency, e.truth.confidence);
    }
}
