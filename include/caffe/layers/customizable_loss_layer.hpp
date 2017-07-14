/*
 * customizable_loss_layer.hpp
 *
 *  Created on: 14 jul. 2017
 *      Author: Juan Maria Gomez Lopez <juanecito@hotmail.com>
 */

#ifndef CAFFE_LAYERS_CUSTOMIZABLE_LOSS_LAYER_HPP_
#define CAFFE_LAYERS_CUSTOMIZABLE_LOSS_LAYER_HPP_

#include <vector>
#include <functional>
#include <memory>

#include "caffe/blob.hpp"
#include "caffe/layer.hpp"
#include "caffe/proto/caffe.pb.h"

#include "caffe/layers/loss_layer.hpp"

namespace caffe {

/**
 * @brief
 */
template <typename Dtype>
class CustomizableLossLayer : public LossLayer<Dtype> {
 public:
  explicit CustomizableLossLayer(const LayerParameter& param)
      : LossLayer<Dtype>(param), diff_()
		{
  	  	  alter_forward_cpu_ = 0;
	  	  alter_forward_gpu_ = 0;
	  	  alter_backward_cpu_ = 0;
	  	  alter_backward_gpu_ = 0;
		}
  virtual void LayerSetUp(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top);

  virtual inline const char* type() const { return "CustomizableLoss"; }

  void set_alter_forward_cpu(std::function<void(const vector<Blob<Dtype>*>&,
	  	  	  const vector<Blob<Dtype>*>&)> alter_forward_cpu)
  	  { alter_forward_cpu_ = alter_forward_cpu;}

  void set_alter_forward_gpu(std::function<void(const vector<Blob<Dtype>*>&,
  	  	  const vector<Blob<Dtype>*>&)> alter_forward_gpu)
	  { alter_forward_gpu_ = alter_forward_gpu;}

  void set_alter_backward_cpu(std::function<void(const vector<Blob<Dtype>*>&,
		  const vector<bool>&, const vector<Blob<Dtype>*>&)> alter_backward_cpu)
  	  { alter_backward_cpu_ = alter_backward_cpu;}

  void set_alter_backward_gpu(std::function<void(const vector<Blob<Dtype>*>&,
		  const vector<bool>&, const vector<Blob<Dtype>*>&)> alter_backward_gpu)
  	  { alter_backward_gpu_ = alter_backward_gpu;}

 protected:
  /// @copydoc CustomizableLossLayer
  virtual void Forward_cpu(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top);
  virtual void Forward_gpu(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top);

  /**
   * @brief
   */
  virtual void Backward_cpu(const vector<Blob<Dtype>*>& top,
      const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);
  virtual void Backward_gpu(const vector<Blob<Dtype>*>& top,
      const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);

  Blob<Dtype> diff_;  // cached for backward pass
  Blob<Dtype> dist_sq_;  // cached for backward pass
  Blob<Dtype> diff_sq_;  // tmp storage for gpu forward pass
  Blob<Dtype> summer_vec_;  // tmp storage for gpu forward pass

  std::function<void(const vector<Blob<Dtype>*>&,
		  	  	  	  const vector<Blob<Dtype>*>&)> alter_forward_cpu_;
  std::function<void(const vector<Blob<Dtype>*>&,
		  	  	  	  const vector<Blob<Dtype>*>&)> alter_forward_gpu_;

  std::function<void(const vector<Blob<Dtype>*>&, const vector<bool>&,
		  	  	  	  const vector<Blob<Dtype>*>&)> alter_backward_cpu_;
  std::function<void(const vector<Blob<Dtype>*>&, const vector<bool>&,
		  	  	  	  const vector<Blob<Dtype>*>&)> alter_backward_gpu_;
};

}  // namespace caffe



#endif /* CAFFE_LAYERS_CUSTOMIZABLE_LOSS_LAYER_HPP_ */
