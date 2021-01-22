#ifndef SRC_FRAMEWORK_FRAME_HPP
#define SRC_FRAMEWORK_FRAME_HPP
class App;
class Frame{
protected:
    App* app;
public:
    virtual void begin()=0;
    virtual void render()=0;
    virtual void finish()=0;
    void setParent(App* parent);
    virtual ~Frame();
};
#endif