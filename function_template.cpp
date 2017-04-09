/**
 * @file function_template.cpp
 * @brief
 * @version 1.0
 * @date 12/09/2016 09:49:02 AM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2016 Tencent. All Rights Reserved.
 */
#include <vector>
#include <iostream>

#include <stdint.h>

typedef int vec_t;
typedef char label_t;
typedef uint64_t tensor_t;

#define STDCOUT std::cout << '[' << __FUNCTION__ << ':' << __LINE__ << ']'

enum Enum {
    nop,  
};

enum {
    CNN_TASK_SIZE = 100,
};

/**
 * @brief 
 * @class Test
 */
class Test
{
public:
    template <typename Error, typename Optimizer,
              typename OnBatchEnumerate, typename OnEpochEnumerate>
    bool train(Optimizer&                  optimizer,
               const std::vector<vec_t>&   inputs,
               const std::vector<label_t>& class_labels,
               size_t                      batch_size,
               int                         epoch,
               OnBatchEnumerate            on_batch_enumerate,
               OnEpochEnumerate            on_epoch_enumerate,
               const bool                  reset_weights = false,
               const int                   n_threads = CNN_TASK_SIZE,
               const std::vector<vec_t>&   t_cost = std::vector<vec_t>()) {
        std::vector<tensor_t> input_tensor, output_tensor, t_cost_tensor;

        STDCOUT << std::endl;
        return fit<Error>(optimizer, input_tensor, output_tensor, batch_size,
                          epoch, on_batch_enumerate, on_epoch_enumerate,
                          reset_weights, n_threads, t_cost_tensor);
    }

#if 1
    template <typename Error, typename Optimizer,
              typename OnBatchEnumerate, typename OnEpochEnumerate,
              typename T, typename U>
    bool fit(Optimizer&            optimizer,
             const std::vector<T>& inputs,
             const std::vector<U>& desired_outputs,
             size_t                batch_size,
             int                   epoch,
             OnBatchEnumerate      on_batch_enumerate,
             OnEpochEnumerate      on_epoch_enumerate,
             const bool            reset_weights = false,
             const int             n_threads = CNN_TASK_SIZE,
             const std::vector<U>& t_cost = std::vector<U>()) {
        std::vector<tensor_t> input_tensor, output_tensor, t_cost_tensor;

        STDCOUT << std::endl;
        return fit<Error>(optimizer, input_tensor, output_tensor, batch_size,
                          epoch, on_batch_enumerate, on_epoch_enumerate,
                          reset_weights, n_threads, t_cost_tensor);
    }
#endif

    template<typename Error, typename Optimizer, typename T, typename U>
    bool fit(Optimizer&            optimizer,
             const std::vector<T>& inputs,
             const std::vector<U>& desired_outputs,
             size_t                batch_size = 1,
             int                   epoch = 1) {
        STDCOUT << std::endl;
        return fit<Error>(optimizer, inputs, desired_outputs,
                          batch_size, epoch, nop, nop);
    }
protected:
private:
    template <typename Error, typename Optimizer,
              typename OnBatchEnumerate, typename OnEpochEnumerate>
    bool fit(Optimizer&                   optimizer,
        const std::vector<tensor_t>& inputs,
        const std::vector<tensor_t>& desired_outputs,
        size_t                       batch_size,
        int                          epoch,
        OnBatchEnumerate             on_batch_enumerate,
        OnEpochEnumerate             on_epoch_enumerate,
        const bool                   reset_weights = false,
        const int                    n_threads = CNN_TASK_SIZE,
        const std::vector<tensor_t>& t_cost = std::vector<tensor_t>()) {

        Error e = 'x';

        STDCOUT << e << std::endl;

        return true;
    }
};

int main() {
    Test t;
    std::vector<vec_t>   inputs;
    std::vector<label_t> class_labels;
    char buf[128];

    t.train<int>(buf, inputs, class_labels, 1, 2, nop, nop);
    std::cout << "======" << std::endl;
    t.fit<char>(buf, inputs, class_labels, 1, 2);

    return 0;
}
