// RUN: %amp_device -c -S -emit-llvm %s -o-|%cppfilt|%FileCheck %s
class base {
 public:
  __attribute__((annotate("deserialize"))) /* For compiler */
  base(float a_,float b_) restrict(amp) :a(a_), b(b_) {}
  float a;
  float b;
};

class baz:public base {
  public:
#if 0 // This declaration is supposed to be generated
  __attribute__((annotate("deserialize"))) /* For compiler */
  baz(float a, float b, int foo) restrict(amp);
#endif
  void cho(void) restrict(amp) {};

  int bar;
};

int kerker(void) restrict(amp,cpu) {
  // Will pass if deserializer declaration and definition are generated
  baz bl(0.0, 0.0, 1);
  return bl.bar;
}

// The definition should be generated by clang
// CHECK: define {{.*}}void @baz::baz(float, float, int)(