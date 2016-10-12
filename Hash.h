#ifndef HASH_H
#define HASH_H

#include <QString>

static int Hash(QString string) {
	long int finalInt = 0;

	int count = 1;
	for (char c : string.toStdString()) {
		finalInt += int(c) * count + 1;

		count += 128;
	}

	finalInt = finalInt;

	return finalInt;
}

#endif //HASH_H