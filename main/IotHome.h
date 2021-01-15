
#define PIN_1 1
#define PIN_2 2
#define PIN_3 3
#define PIN_4 4
#define PIN_5 5
#define PIN_6 6
#define PIN_7 7

class IotHome {
public:
	IotHome();
	void init();
	void tryOn(int pin);
	void tryOff(int pin);
};
