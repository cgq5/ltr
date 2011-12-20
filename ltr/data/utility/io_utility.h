// Copyright 2011 Yandex

#ifndef LTR_DATA_UTILITY_IO_UTILITY_H_
#define LTR_DATA_UTILITY_IO_UTILITY_H_

#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <fstream>

#include "ltr/data/data_set.h"
#include "ltr/data/utility/parsers/object_parser.h"

#include "ltr/scorers/scorer.h"
#include "ltr/utility/numerical.h"

using std::string;
using std::map;
using std::vector;

namespace ltr {
namespace io_utility {
/**
 * @function loadDataSet
 * Function to load data set from file.
 * @param filename - path to file
 * @param format - data format (svmlite, yandex, arff)
 * @param handler - class, converting features into vector of numbers
 */
template<class TElement>
DataSet<TElement> loadDataSet(const string& filename,
    const string& format,
    NominalFeatureHandler::Ptr handler =
        NominalFeatureHandler::Ptr(new RemoveHandler()));
/**
 * @function saveDataSet
 * Function to save data set into file.
 * @param data - data set to save
 * @param filename - path to file
 * @param format - data format (svmlite, yandex, arff) 
 */
template<class TElement>
void saveDataSet(const DataSet<TElement>& data,
    const string& filename,
    const string& format);
/**
 * @function buildDataSet
 * Function to build data set of given objects
 * @param parser - parser, which will build data set
 * @param objects - objects to build data set from
 * @param info - information about features in objects
 */
template<class TElement>
DataSet<TElement> buildDataSet(IParser::Ptr parser,
    const vector<Object>& objects,
    const FeatureInfo& info);
/**
 * @function savePredictions
 * Function to save predicted labeles for given data set
 * @param data - data set to predict
 * @param scorer - scorer for prediction
 * @param filename - path to file
 */
template<class TElement>
void savePredictions(const DataSet<TElement>& data,
    Scorer::Ptr scorer,
    string filename);
};
};

// Template realization
namespace ltr {
namespace io_utility {

template<class TElement>
DataSet<TElement> loadDataSet(const string& filename,
    const string& format,
    NominalFeatureHandler::Ptr handler) {
  std::ifstream file(filename.c_str());
  if (file.fail())
    throw std::logic_error("File " + filename + " not found");
  IParser::Ptr parser = getParser(format);
  parser->init(&file);
  handler->init(parser->info());

  vector<Object> objects;
  std::string line;
  while (std::getline(file, line))
    try {
      objects.push_back(parser->parse(line, handler));
    } catch(IParser::comment err) {}

  file.close();
  return buildDataSet<TElement>(parser, objects, handler->featureInfo());
}


template<class TElement>
void saveDataSet(const DataSet<TElement>& data,
    const string& filename,
    const string& format) {
  std::ofstream file(filename.c_str());
  if (file.fail())
    throw std::logic_error("can't open " + filename + " for writing");
  IParser::Ptr parser = getParser(format);
  for (size_t i = 0; i < data.size(); i++)
    for (size_t j = 0; j < data[i].size(); j++) {
      parser->writeString(data[i][j], &file);
      file << std::endl;
    }
  file.close();
}

template<class TElement>
void savePredictions(const DataSet<TElement>& data,
    Scorer::Ptr scorer,
    string filename) {
  std::ofstream file(filename.c_str());

  if (file.fail()) {
    throw std::logic_error("can't open " + filename + " for writing");
  }

  file.precision(utility::DOUBLE_PRECISION);
  for (size_t i = 0; i < data.size(); i++)
    for (size_t j = 0; j < data[i].size(); j++) {
      file << (*scorer)(data[i][j]) << std::endl;
    }
  file.close();
}
};
}
#endif  // LTR_DATA_UTILITY_IO_UTILITY_H_
