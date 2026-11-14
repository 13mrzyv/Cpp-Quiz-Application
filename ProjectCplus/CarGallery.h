#pragma once
class CarGallery
{
public:
	const char* name;
	Car* cars;
	int* countOfCars;


	CarGallery(const char* name, Car* cars, int* countOfCars);
	void ShowCarsInGallery();
	void AddCar(Car car);
	void DeleteCarById(int id);
	void GetById(int id);

};

CarGallery::CarGallery(const char* name, Car* cars, int* countOfCars) {
	this->name = name;
	this->cars = cars;
	this->countOfCars = countOfCars;
}
void CarGallery::ShowCarsInGallery() {
	for (size_t i = 0; i < *countOfCars; i++)
	{
		cars[i].ShowCar();
	}
}
void CarGallery::AddCar(Car car) {
	(*countOfCars)++;
	Car* carsTemp = new Car[*countOfCars];
	for (size_t i = 0; i < *countOfCars - 1; i++)
	{
		carsTemp[i] = cars[i];
	}
	carsTemp[*countOfCars - 1] = car;
	delete[] cars;
	cars = nullptr;
	cars = carsTemp;
}
void CarGallery::DeleteCarById(int id) {
	(*countOfCars)--;
	int index = 0;
	Car* carsTemp = new Car[*countOfCars];

	for (size_t i = 0; i < *countOfCars + 1; i++)
	{
		if (cars[i].id != id)
		{
			carsTemp[index] = cars[i];
			index++;
		}
	}
	delete[] cars;
	cars = nullptr;
	cars = carsTemp;
}
void CarGallery::GetById(int id) {
	for (size_t i = 0; i < *countOfCars; i++)
	{
		if (cars[i].id == id)
		{
			cars[i].ShowCar();
		}
	}
}

