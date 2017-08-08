/*
 * weak reference
 * container and element
 * 目标：不管哪一方先挂掉，软件都应该有正确的状态，不会飞掉
 * 要点：
 * （1）双方持有指向对方的弱引用，只有在调用对方时才转换成强引用
 * （2）单方面解除联系，容器类不再负责元素的生命周期，但元素死掉之前一定从容器中删除掉
 * （3）对容器的增删操作线程安全
 * （4）持有指向元素的引用，但不涉及元素的生命周期
 */

#include <memory>
#include <mutex>
#include <thread>
#include <unordered_map>
#include <iostream>
#include <string>

class session : public std::enable_shared_from_this<session> {
public:
    typedef std::shared_ptr<session> ptr;

    std::string name;

    ~session(){
        std::cout<< name <<" deleted" <<std::endl;
    }
};

class container : public std::enable_shared_from_this<container> {
public:
    typedef std::shared_ptr<container> ptr;

    ~container() {
        std::cout<< "container deleted " << std::endl;
    }

    session::ptr get(const std::string & name) {

        std::unique_lock<std::mutex> lock(m);

        std::weak_ptr<session> & p = eles[name]; // reference
        auto shared = p.lock();
        if( shared )
            return shared;

        std::shared_ptr<session> s(new session, this->deleter());
        s->name = name;
        p = s;
        return s;
    }

    void remove(const std::string & name) {
        std::unique_lock<std::mutex> lock(m);
        eles.erase(name);
        std::cout<<name<<" removed"<<std::endl;
    }

private:
    std::function<void(session *)> deleter() {
        std::weak_ptr<container> self = this->shared_from_this();
        auto del = [self](session * p ){
            auto shared = self.lock();
            if( shared ) {
                shared->remove(p->name);
            }
            delete p;
        };
        return del;
    }

private:
    std::mutex m;
    std::unordered_map<std::string, std::weak_ptr<session> > eles;
};


int main(int argc, char *argv[])
{
    container::ptr c = std::make_shared<container>();

    auto a = c->get("a");
    auto b = c->get("a");
    auto d = c->get("d");
    auto e = c->get("e");

    a.reset();
    b.reset();
    d.reset();
    c.reset();
    e.reset();

    return 0;
}
