#include <iostream>
#include <vector>
#include <memory>
#include <string>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(float temperature, float humidity, float pressure) = 0;
};

class Subject {
public:
    virtual ~Subject() = default;
    virtual void addObserver(std::shared_ptr<Observer> observer) = 0;
    virtual void removeObserver(std::shared_ptr<Observer> observer) = 0;
    virtual void notifyObservers() = 0;
};

class WeatherStation : public Subject {
private:
    std::vector<std::shared_ptr<Observer>> observers;
    float temperature;
    float humidity;
    float pressure;

public:
    void setWeatherData(float temp, float hum, float pres) {
        temperature = temp;
        humidity = hum;
        pressure = pres;
        notifyObservers();
    }

    void addObserver(std::shared_ptr<Observer> observer) override {
        observers.push_back(observer);
    }

    void removeObserver(std::shared_ptr<Observer> observer) override {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notifyObservers() override {
        for (const auto& observer : observers) {
            observer->update(temperature, humidity, pressure);
        }
    }
};

class CurrentConditionsDisplay : public Observer {
public:
    void update(float temperature, float humidity, float pressure) override {
        std::cout << "Current Conditions: " << temperature 
                  << "°C, " << humidity << "% humidity, " 
                  << pressure << " hPa" << std::endl;
    }
};

class StatisticsDisplay : public Observer {
private:
    float maxTemp = -1000.0;
    float minTemp = 1000.0;
    float tempSum = 0.0;
    int numReadings = 0;

public:
    void update(float temperature, float humidity, float pressure) override {
        tempSum += temperature;
        numReadings++;
        if (temperature > maxTemp) maxTemp = temperature;
        if (temperature < minTemp) minTemp = temperature;

        std::cout << "Statistics: Avg/Max/Min temperature = " 
                  << (tempSum / numReadings) << "/" << maxTemp 
                  << "/" << minTemp << "°C" << std::endl;
    }
};

int main() {
    auto weatherStation = std::make_shared<WeatherStation>();

    auto currentDisplay = std::make_shared<CurrentConditionsDisplay>();
    auto statsDisplay = std::make_shared<StatisticsDisplay>();

    weatherStation->addObserver(currentDisplay);
    weatherStation->addObserver(statsDisplay);

    std::cout << "Weather Update 1:" << std::endl;
    weatherStation->setWeatherData(25.0f, 65.0f, 1013.0f);

    std::cout << "\nWeather Update 2:" << std::endl;
    weatherStation->setWeatherData(30.0f, 70.0f, 1010.0f);

    std::cout << "\nRemoving Current Conditions" << std::endl;
    weatherStation->removeObserver(currentDisplay);

    std::cout << "\nWeather Update 3:" << std::endl;
    weatherStation->setWeatherData(28.0f, 60.0f, 1012.0f);

    return 0;
}