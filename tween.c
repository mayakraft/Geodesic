#include <stdlib.h>
#include <string.h>

struct tween {
	flo_t           *data;  // data in its present state/frame
	unsigned int    count;  // data count

	flo_t           *dataNaught;  // data at start, 0.0;
	flo_t           *dataVector;  // change in data from 0.0 to 1.0
};

typedef struct tween tween;

// data types must match!
tween makeTween(flo_t *dataNaught, flo_t *dataVector, unsigned int count){
	tween t;
	t.count = count;
	t.data = malloc(sizeof(flo_t) * count);
	t.dataVector = malloc(sizeof(flo_t) * count);
	t.dataNaught = malloc(sizeof(flo_t) * count);
	// flo_t data type must match flo_t type in struct tween definition
	memcpy(t.dataVector, dataVector, sizeof(flo_t) * count);
	memcpy(t.dataNaught, dataNaught, sizeof(flo_t) * count);
	memcpy(t.data, dataNaught, sizeof(flo_t) * count);
	return t;
	// if types don't match, use this below
	// for(int i = 0; i < count; i++){
	// 	t.dataNaught[i] = dataNaught[i];
	// 	t.dataVector[i] = dataVector[i];
	//  t.data[i] = dataNaught[i];
	// }
}

void deleteTween(tween *t){
	free(t->dataVector);
	free(t->dataNaught);
	free(t->data);
}

// frame: tween progress, traditionally 0.0 - 1.0
void updateTween(tween *t, float frame){
	for(int i = 0; i < t->count; i++){
		t->data[i] = t->dataNaught[i] + t->dataVector[i] * frame;
	}
}