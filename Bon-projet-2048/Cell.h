class Cell {
private:
	int value;

public:
	Cell() : value(0) {}

	void display() const;

	int getValue() const;

	void setValue(int val);

	bool isEmpty() const;
};