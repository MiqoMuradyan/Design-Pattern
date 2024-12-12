#include <iostream>
#include <string>

class Amplifier {
public:
    void on() {
        std::cout << "Amplifier: On" << std::endl;
    }

    void off() {
        std::cout << "Amplifier: Off" << std::endl;
    }

    void setVolume(int level) {
        std::cout << "Amplifier: Volume set to " << level << std::endl;
    }
};

class DVDPlayer {
public:
    void on() {
        std::cout << "DVD Player: On" << std::endl;
    }

    void off() {
        std::cout << "DVD Player: Off" << std::endl;
    }

    void play(const std::string& movie) {
        std::cout << "DVD Player: Playing \"" << movie << "\"" << std::endl;
    }

    void stop() {
        std::cout << "DVD Player: Stop playing" << std::endl;
    }
};

class Projector {
public:
    void on() {
        std::cout << "Projector: On" << std::endl;
    }

    void off() {
        std::cout << "Projector: Off" << std::endl;
    }

    void wideScreenMode() {
        std::cout << "Projector: Set to widescreen mode" << std::endl;
    }
};

class Lights {
public:
    void dim(int level) {
        std::cout << "Lights: Dimming to " << level << "%" << std::endl;
    }

    void on() {
        std::cout << "Lights: On" << std::endl;
    }
};

class HomeTheaterFacade {
private:
    Amplifier amplifier;
    DVDPlayer dvdPlayer;
    Projector projector;
    Lights lights;

public:
    HomeTheaterFacade(Amplifier amp, DVDPlayer dvd, Projector proj, Lights light)
        : amplifier(std::move(amp)), dvdPlayer(std::move(dvd)), projector(std::move(proj)), lights(std::move(light)) {}

    void watchMovie(const std::string& movie) {
        std::cout << "Get ready to watch a movie!" << std::endl;
        lights.dim(30);
        projector.on();
        projector.wideScreenMode();
        amplifier.on();
        amplifier.setVolume(10);
        dvdPlayer.on();
        dvdPlayer.play(movie);
    }

    void endMovie() {
        std::cout << "Shutting down the home theater..." << std::endl;
        dvdPlayer.stop();
        dvdPlayer.off();
        amplifier.off();
        projector.off();
        lights.on();
    }
};

int main() {
    Amplifier amp;
    DVDPlayer dvd;
    Projector proj;
    Lights light;

    HomeTheaterFacade homeTheater(amp, dvd, proj, light);

    homeTheater.watchMovie("Inception");
    std::cout << std::endl;
    homeTheater.endMovie();

    return 0;
}