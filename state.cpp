#include <iostream>
#include <memory>
#include <string>

class MusicPlayer {
private:
    std::shared_ptr<State> currentState;

public:
    explicit MusicPlayer(std::shared_ptr<State> state) : currentState(std::move(state)) {}

    void setState(std::shared_ptr<State> state) {
        currentState = std::move(state);
    }

    void play() {
        currentState->play(*this);
    }

    void pause() {
        currentState->pause(*this);
    }

    void stop() {
        currentState->stop(*this);
    }

    void showState() {
        std::cout << "Current State: " << currentState->getStateName() << std::endl;
    }
};

class State {
public:
    virtual ~State() = default;
    virtual void play(MusicPlayer& player) = 0;
    virtual void pause(MusicPlayer& player) = 0;
    virtual void stop(MusicPlayer& player) = 0;
    virtual std::string getStateName() const = 0;
};

class PlayingState : public State {
public:
    void play(MusicPlayer& player) override {
        std::cout << "Music is already playing!" << std::endl;
    }

    void pause(MusicPlayer& player) override {
        std::cout << "Pausing the music." << std::endl;
        player.setState(std::make_shared<PausedState>());
    }

    void stop(MusicPlayer& player) override {
        std::cout << "Stopping the music." << std::endl;
        player.setState(std::make_shared<StoppedState>());
    }

    std::string getStateName() const override {
        return "Playing";
    }
};

class PausedState : public State {
public:
    void play(MusicPlayer& player) override {
        std::cout << "Resuming the music." << std::endl;
        player.setState(std::make_shared<PlayingState>());
    }

    void pause(MusicPlayer& player) override {
        std::cout << "Music is already paused!" << std::endl;
    }

    void stop(MusicPlayer& player) override {
        std::cout << "Stopping the music from paused state." << std::endl;
        player.setState(std::make_shared<StoppedState>());
    }

    std::string getStateName() const override {
        return "Paused";
    }
};

class StoppedState : public State {
public:
    void play(MusicPlayer& player) override {
        std::cout << "Starting the music." << std::endl;
        player.setState(std::make_shared<PlayingState>());
    }

    void pause(MusicPlayer& player) override {
        std::cout << "Cannot pause. Music is stopped!" << std::endl;
    }

    void stop(MusicPlayer& player) override {
        std::cout << "Music is already stopped!" << std::endl;
    }

    std::string getStateName() const override {
        return "Stopped";
    }
};

int main() {
    auto stoppedState = std::make_shared<StoppedState>();
    MusicPlayer player(stoppedState);

    player.showState();
    player.play();
    player.showState();
    player.pause();
    player.showState();
    player.stop();
    player.showState();
    player.stop();

    return 0;
}