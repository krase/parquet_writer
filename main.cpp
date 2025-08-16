#include <iostream>

#include "arrow/io/file.h"
#include "parquet/stream_writer.h"
#include "parquet/arrow/writer.h"
#include "arrow/util/type_fwd.h"

using arrow::Compression;
using parquet::ParquetDataPageVersion;
using parquet::ParquetVersion;
using parquet::WriterProperties;

int main()
{

    std::cout << "Hallo\n";

    std::shared_ptr<arrow::io::FileOutputStream> outfile;

    PARQUET_ASSIGN_OR_THROW(
        outfile,
        arrow::io::FileOutputStream::Open("../test.parquet"));

    parquet::WriterProperties::Builder builder;

    std::shared_ptr<WriterProperties> props = WriterProperties::Builder()
                                                  .max_row_group_length(64 * 1024)
                                                  ->created_by("My Application")
                                                  ->version(ParquetVersion::PARQUET_2_6)
                                                  ->data_page_version(ParquetDataPageVersion::V2)
                                                  ->compression(Compression::SNAPPY)
                                                  ->enable_dictionary()
                                                  ->build();

    std::shared_ptr<parquet::schema::GroupNode> schema;
    parquet::schema::NodeVector fields;
    fields.push_back(parquet::schema::PrimitiveNode::Make(
        "A", parquet::Repetition::REQUIRED, parquet::Type::INT32, parquet::ConvertedType::INT_32));
    fields.push_back(parquet::schema::PrimitiveNode::Make(
        "B", parquet::Repetition::REQUIRED, parquet::Type::INT32, parquet::ConvertedType::INT_32));
    fields.push_back(parquet::schema::PrimitiveNode::Make(
        "C", parquet::Repetition::REQUIRED, parquet::Type::INT32, parquet::ConvertedType::INT_32));
    schema = std::static_pointer_cast<parquet::schema::GroupNode>(
        parquet::schema::GroupNode::Make("schema", parquet::Repetition::REQUIRED, fields));

    parquet::StreamWriter os{
        parquet::ParquetFileWriter::Open(outfile, schema, builder.build())};


   // Loop over some data structure which provides the required
   // fields to be written and write each row.
   for (const auto& a : {1,2,3})
   {
       std::cout << a * 2 << " " << a * 3 << " " << a * 4 << " " << std::endl;
       os << a * 2 << a * 3 << a * 4 << parquet::EndRow;
   }

   //os.EndRowGroup();
   //auto status = outfile->Close();

   return 0;
}