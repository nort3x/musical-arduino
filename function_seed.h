//
// Created by root on 5/16/21.
//

#ifndef FUNCTIONGENERATOR_SEEDFUNCTION_H
#define FUNCTIONGENERATOR_SEEDFUNCTION_H



namespace ttic {
    template<typename T>
    struct PeriodicFunction {
        size_t range;
        T *function;
    public:
    PeriodicFunction() = default;
    
        PeriodicFunction(T(*func)(int), size_t range) {

            this->range = range;
            this->function = new T[range]();
            for (int i = 0; i < range; ++i) {
                function[i] = func(i);
            }
        }
        PeriodicFunction(const PeriodicFunction& pf){

            range = pf.range;
            function = new T[range];
            for(int i=0;i<range;++i)
            function[i] = pf.function[i];

        }
        PeriodicFunction(PeriodicFunction&& stealable) noexcept {

            range =stealable.range;
            function = stealable.function;
            stealable.function = nullptr;
        }
        PeriodicFunction& operator=(const PeriodicFunction& pf){

            if(this!=&pf)
            {
                delete[] function;
                function = pf.function;
                range = pf.range;
            }
        }

        virtual ~PeriodicFunction() {

            delete[] function;
        }

        T operator()(int i){
            return function[i % range];
        }


    };

    template<typename T, typename K>
    struct FunctionCluster {

        struct Pair {
            T freq;
            K del;
        };

    private:
         PeriodicFunction<T> freqFunc;
         PeriodicFunction<K> delayFunc;
    public:

        FunctionCluster(const PeriodicFunction<T> &freqFunc,const PeriodicFunction<K>& delayFunc) :
                freqFunc(freqFunc), delayFunc(delayFunc) {

        }

       


        Pair operator()(int i) {
            return {freqFunc(i), delayFunc(i)};
        }



    };

}

#endif //FUNCTIONGENERATOR_SEEDFUNCTION_H
