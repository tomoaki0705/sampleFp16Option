#include <iostream>
#include <stdio.h>

bool checkFp16Support()
{
  int cpuid_data[4] = { 0, 0, 0, 0 };

  #ifdef __x86_64__
  asm __volatile__
  (
   "movl $1, %%eax\n\t"
   "cpuid\n\t"
   :[eax]"=a"(cpuid_data[0]),[ebx]"=b"(cpuid_data[1]),[ecx]"=c"(cpuid_data[2]),[edx]"=d"(cpuid_data[3])
   :
   : "cc"
  );
  #else
  asm volatile
  (
   "pushl %%ebx\n\t"
   "movl $1,%%eax\n\t"
   "cpuid\n\t"
   "popl %%ebx\n\t"
   : "=a"(cpuid_data[0]), "=c"(cpuid_data[2]), "=d"(cpuid_data[3])
   :
   : "cc"
  );
  #endif

  return ((cpuid_data[2] & (1<<29)) != 0);
}

#if defined __F16C__ || (defined _MSC_VER && _MSC_VER >= 1700)
#include <immintrin.h>
int test()
{
#ifdef __GNUC__
    const float __attribute__ ((aligned (16))) src[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    short __attribute__ ((aligned (16))) dst[8];
#elif defined _MSC_VER
    const float __declspec(align(16)) src[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    short __declspec(align(16)) dst[8];
#else
    const float src[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    short dst[8];
#endif

  if(checkFp16Support())
  {
    __m128 v_src = _mm_load_ps(src);
    __m128i v_dst = _mm_cvtps_ph(v_src, 0);
    _mm_storel_epi64((__m128i*)dst, v_dst);
    return (int)dst[0];
  }
  else
  {
    return 1;
  }
}
#else
#error "FP16 is not supported"
#endif

int main()
{
  std::cout << "Hello World!" << std::endl;
  printf("%d\n", test());
  return 0;
}
