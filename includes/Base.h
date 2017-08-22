
class Base{

public:

	Base(bool b): val(b){
		isBool = true;
	}

	Base(int i): value(i){}

	int getValue(){
		return value;
	}

	bool hasBooleanValue(){
		return isBool;
	}

	bool getBooleanValue(){
		return val;
	}

	std::string getBoolString(){
		return val? "true" : "false";
	}

private:
	bool isBool = false;
	bool val;

	int value;

};