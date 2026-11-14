class Car
{
public:
	int id;
	const char* marka;
	const char* model;
	const char* color;
	short year;

	Car();
	Car(int id, const char* marka, const char* model, const char* color, short year);
	explicit Car(int id);
	Car(int id, const char* marka);
	Car(int id, const char* marka, const char* model);
	void ShowCar();


};

Car::Car()
{
	this->id = 0;
	this->marka = "No marka";
	this->model = "No marka";
	this->color = "No marka";
	this->year = 0;
}
Car::Car(int id, const char* marka, const char* model, const char* color, short year)
{
	this->id = id;
	this->marka = marka;
	this->model = model;
	this->color = color;
	this->year = year;
}
Car::Car(int id) {
	this->id = id;
	this->marka = "No marka";
	this->model = "No marka";
	this->color = "No marka";
	this->year = 0;
}
Car::Car(int id, const char* marka)
{
	this->id = id;
	this->marka = marka;
	this->model = "No marka";
	this->color = "No marka";
	this->year = 0;
}
Car::Car(int id, const char* marka, const char* model)
{
	this->id = id;
	this->marka = marka;
	this->model = model;
	this->color = "No marka";
	this->year = 0;
}
void Car::ShowCar() {
	cout << "Car id: " << id << endl;
	cout << "Car marka: " <<marka << endl;
	cout << "Car model: " << model << endl;
	cout << "Car color: " <<color << endl;
	cout << "Car year: " <<year << endl;
	cout << endl;
}
