
#include <sstream>

#include <olc/ir/Type.h>

int main() {
  using namespace olc;

  IntegerType *intType = IntegerType::get();
  FloatType *floatType = FloatType::get();
  PointerType *i32PtrType = PointerType::get(intType);
  PointerType *f32PtrPtrType = PointerType::get(PointerType::get(floatType));

  // 类型唯一性
  assert(intType == IntegerType::get());
  assert(floatType == FloatType::get());
  assert(i32PtrType == PointerType::get(intType));
  // 类型区分
  assert(i32PtrType != PointerType::get(floatType));
  assert(i32PtrType != f32PtrPtrType);

  auto print_to_str = [](Type *type) {
    std::ostringstream oss;
    type->print(oss);
    return oss.str();
  };

  // print 测试
  assert(print_to_str(intType) == "i32");
  assert(print_to_str(floatType) == "f32");
  assert(print_to_str(i32PtrType) == "i32*");
  assert(print_to_str(f32PtrPtrType) == "f32**");

  return 0;
}
