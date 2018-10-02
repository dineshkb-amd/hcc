
// RUN: %hc %s -o %t.out && %t.out

#include <hc/hc.hpp>

#include <iostream>

// a test which checks accelerator::get_profile()
bool test() {

  hc::accelerator acc;

  bool ret = true;

  // check if the accelerator is HSA
  if (acc.is_hsa_accelerator()) {

    // check if we can get its profile
    hc::accelerator_profile profile = acc.get_profile();

    // an HSA agent must have its profile specified
    ret &= (profile != hc::accelerator_profile_none);
  }

  return ret;
}

int main() {
  bool ret = true;

  ret &= test();

  return !(ret == true);
}

