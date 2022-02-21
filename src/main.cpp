#include <chrono>
#include <iostream>
#include "../include/bakery.hpp"
using namespace std::chrono;

int main() {
  
  auto bakerySmall = text_deserializer("../data/small.txt");
  auto bakeryMedium = text_deserializer("../data/medium.txt");
  auto bakeryLarge = text_deserializer("../data/large.txt");

  /* Timing text serialization */

  // Small text
  auto start_textSmall = high_resolution_clock::now();
  text_serializer(bakerySmall, "../data/serializedTextSmall.txt");
  auto end_textSmall = high_resolution_clock::now();
  int ser_small_text = duration_cast<milliseconds>(end_textSmall - start_textSmall).count();

  // Medium text
  auto start_textMedium = high_resolution_clock::now();
  text_serializer(bakeryMedium, "../data/serializedTextMedium.txt");
  auto end_textMedium = high_resolution_clock::now();
  int ser_medium_text = duration_cast<milliseconds>(end_textMedium - start_textMedium).count();

  // Large text
  auto start_textLarge = high_resolution_clock::now();
  text_serializer(bakeryLarge, "../data/serializedTextLarge.txt");
  auto end_textLarge = high_resolution_clock::now();
  int ser_large_text = duration_cast<milliseconds>(end_textLarge - start_textLarge).count();
  

  /* Timing text deserialization */
  
  // Small text
  auto d_start_textSmall = high_resolution_clock::now();
  text_deserializer("../data/serializedTextSmall.txt");
  auto d_end_textSmall = high_resolution_clock::now();
  int deser_small_text = duration_cast<milliseconds>(d_end_textSmall - d_start_textSmall).count();

  // Medium text
  auto d_start_textMedium = high_resolution_clock::now();
  text_deserializer("../data/serializedTextMedium.txt");
  auto d_end_textMedium = high_resolution_clock::now();
  int deser_medium_text = duration_cast<milliseconds>(d_end_textMedium - d_start_textMedium).count();

  // Large text
  auto d_start_textLarge = high_resolution_clock::now();
  text_deserializer("../data/serializedTextLarge.txt");
  auto d_end_textLarge = high_resolution_clock::now();
  int deser_large_text = duration_cast<milliseconds>(d_end_textLarge - d_start_textLarge).count();
  
  /* Timing binary serialization */
  
  // Small text
  auto start_binSmall = high_resolution_clock::now();
  text_serializer(bakerySmall, "../data/serializedBinSmall.bin");
  auto end_binSmall = high_resolution_clock::now();
  int ser_small_bin = duration_cast<milliseconds>(end_binSmall - start_binSmall).count();

  // Medium text
  auto start_binMedium = high_resolution_clock::now();
  text_serializer(bakeryMedium, "../data/serializedBinMedium.bin");
  auto end_binMedium = high_resolution_clock::now();
  int ser_medium_bin = duration_cast<milliseconds>(end_binMedium - start_binMedium).count();

  // Large text
  auto start_binLarge = high_resolution_clock::now();
  text_serializer(bakeryLarge, "../data/serializedBinLarge.bin");
  auto end_binLarge = high_resolution_clock::now();
  int ser_large_bin = duration_cast<milliseconds>(end_binLarge - start_binLarge).count();


  /* Timing binary deserialization */ 
  
  // Small text
  auto d_start_binSmall = high_resolution_clock::now();
  text_deserializer("../data/serializedBinSmall.bin");
  auto d_end_binSmall = high_resolution_clock::now();
  int deser_small_bin = duration_cast<milliseconds>(d_end_binSmall - d_start_binSmall).count();

  // Medium text
  auto d_start_binMedium = high_resolution_clock::now();
  text_deserializer("../data/serializedBinMedium.bin");
  auto d_end_binMedium = high_resolution_clock::now();
  int deser_medium_bin = duration_cast<milliseconds>(d_end_binMedium - d_start_binMedium).count();

  // Large text
  auto d_start_binLarge = high_resolution_clock::now();
  text_deserializer("../data/serializedBinLarge.bin");
  auto d_end_binLarge = high_resolution_clock::now();
  int deser_large_bin = duration_cast<milliseconds>(d_end_binLarge - d_start_binLarge).count();


  std::cout << "\t-------- TIMING --------\n";
  
  // Text Serialization
  std::cout << "Text serialization time for small textfile: " << ser_small_text << "ms\n";
  std::cout << "Text serialization time for medium textfile: " << ser_medium_text << "ms\n";
  std::cout << "Text serialization time for large textfile: " << ser_large_text << "ms\n\n";

  // Text Deserialization
  std::cout << "Text deserialization time for small textfile: " << deser_small_text << "ms\n";
  std::cout << "Text deserialization time for medium textfile: " << deser_medium_text << "ms\n";
  std::cout << "Text deserialization time for large textfile: " << deser_large_text << "ms\n\n";

  // Binary Serialization
  std::cout << "Binary serialization time for small textfile: " << ser_small_bin << "ms\n";
  std::cout << "Binary serialization time for medium textfile: " << ser_medium_bin << "ms\n";
  std::cout << "Binary serialization time for large textfile: " << ser_large_bin << "ms\n\n";

  // Binary Deserialization
  std::cout << "Binary deserialization time for small textfile: " << deser_small_bin << "ms\n";
  std::cout << "Binary deserialization time for medium textfile: " << deser_medium_bin << "ms\n";
  std::cout << "Binary deserialization time for large textfile: " << deser_large_bin << "ms\n";

  

  binary_serializer(bakerySmall, "../data/serializedBinSmall.bin");
  binary_deserializer("../data/serializedBinSmall.bin");

  binary_serializer(bakeryMedium, "../data/serializedBinMedium.bin");
  binary_deserializer("../data/serializedBinMedium.bin");

  binary_serializer(bakeryLarge, "../data/serializedBinLarge.bin");
  binary_deserializer("../data/serializedBinLarge.bin");

 /*  binary_serializer(bakerySmall, "../data/binarySmall.bin");
  binary_deserializer("../data/binarySmall.bin");

  binary_serializer(bakeryMedium, "../data/binaryMedium.bin");
  binary_deserializer("../data/binaryMedium.bin");

  binary_serializer(bakeryLarge, "../data/binaryLarge.bin");
  binary_deserializer("../data/binaryLarge.bin"); */



  // Text Serialization and deserialization timing for large text
/*   auto bakery1 = text_deserializer("../data/small.txt");
  auto start_text_ser_small = high_resolution_clock::now();
  text_serializer(bakery1, "../data/serializedTextSmall.txt");
  auto end_text_ser_small = high_resolution_clock::now();
  
  std::cout << "Text serialization for small file took: "
            << duration_cast<milliseconds>(end_text_ser_small - start_text_ser_small).count() << "ms" 
            << std::endl << std::endl; */

  // Text Serialization and deserialization timing for large text
/*   auto bakery2 = text_deserializer("../data/large.txt");
  auto start_text_ser = high_resolution_clock::now();
  text_serializer(bakery2, "../data/serializedLarge.txt");
  auto end_text_ser = high_resolution_clock::now();
  
  int time = duration_cast<milliseconds>(end_text_ser - start_text_ser).count();
  std::cout << "Text serialization took: "
            << duration_cast<milliseconds>(end_text_ser - start_text_ser).count() << "ms" 
            << std::endl << std::endl; */

  /* text_deserializer("../data/serializedSmall.txt"); 
  auto text_deser_time = high_resolution_clock::now() - start;
  std::cout << "Text deserializer took: "
            << duration_cast<milliseconds>(text_deser_time).count() << "ms"
            << std::endl
            << std::endl; */

  /* std::cout << "TESTIng time: " << time << std::endl; */
  return 0;
}


/* 
Questions
- Is the parameter for the text_serializer function
supposed to be where the output from that function
should go? So that once you serialize it, you can 
call the text_deserializer with the path file that you put
fo rthe serializer function? 

*/