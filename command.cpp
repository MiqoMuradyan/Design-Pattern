#include <iostream>
#include <memory>
#include <vector>
#include <string>

class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class Light {
public:
    void on() {
        std::cout << "The light is ON." << std::endl;
    }
    void off() {
        std::cout << "The light is OFF." << std::endl;
    }
};

class Fan {
public:
    void start() {
        std::cout << "The fan is RUNNING." << std::endl;
    }
    void stop() {
        std::cout << "The fan is STOPPED." << std::endl;
    }
};

class LightOnCommand : public Command {
private:
    std::shared_ptr<Light> light;

public:
    explicit LightOnCommand(std::shared_ptr<Light> light) : light(std::move(light)) {}

    void execute() override {
        light->on();
    }

    void undo() override {
        light->off();
    }
};

class LightOffCommand : public Command {
private:
    std::shared_ptr<Light> light;

public:
    explicit LightOffCommand(std::shared_ptr<Light> light) : light(std::move(light)) {}

    void execute() override {
        light->off();
    }

    void undo() override {
        light->on();
    }
};

class StartCommand : public Command {
private:
    std::shared_ptr<Fan> fan;

public:
    explicit StartCommand(std::shared_ptr<Fan> fan) : fan(std::move(fan)) {}

    void execute() override {
        fan->start();
    }

    void undo() override {
        fan->stop();
    }
};

class StopCommand : public Command {
private:
    std::shared_ptr<Fan> fan;

public:
    explicit StopCommand(std::shared_ptr<Fan> fan) : fan(std::move(fan)) {}

    void execute() override {
        fan->stop();
    }

    void undo() override {
        fan->start();
    }
};

class RemoteControl {
private:
    std::vector<std::shared_ptr<Command>> history;

public:
    void executeCommand(std::shared_ptr<Command> command) {
        command->execute();
        history.push_back(command);
    }

    void undoLastCommand() {
        if (!history.empty()) {
            history.back()->undo();
            history.pop_back();
        } else {
            std::cout << "No commands to undo." << std::endl;
        }
    }
};

int main() {
    auto light = std::make_shared<Light>();
    auto fan = std::make_shared<Fan>();

    auto lightOn = std::make_shared<LightOnCommand>(light);
    auto lightOff = std::make_shared<LightOffCommand>(light);
    auto fanStart = std::make_shared<StartCommand>(fan);
    auto fanStop = std::make_shared<StopCommand>(fan);

    RemoteControl remote;

    std::cout << "Executing commands:" << std::endl;
    remote.executeCommand(lightOn);
    remote.executeCommand(fanStart);

    std::cout << "\nUndoing commands:" << std::endl;
    remote.undoLastCommand();
    remote.undoLastCommand();

    std::cout << "\nExecuting more commands:" << std::endl;
    remote.executeCommand(lightOff);
    remote.executeCommand(fanStop);

    std::cout << "\nUndoing last command:" << std::endl;
    remote.undoLastCommand();

    return 0;
}