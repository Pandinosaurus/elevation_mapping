/*
 * PointXYZRGBConfidenceRatio.hpp
 *
 *  Created on: Nov 26, 2020
 *      Author: Magnus Gärtner
 *   Institute: ETH Zurich, ANYbotics
 *
 *   This file defines our custom pcl type, ie including a confidence_ratio.
 *   Adapted from https://github.com/PointCloudLibrary/pcl/blob/master/common/include/pcl/impl/point_types.hpp
 */

#pragma once

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

namespace pcl {

struct _PointXYZRGBConfidenceRatio {
  PCL_ADD_POINT4D;  // This adds the members x,y,z which can also be accessed using the point (which is float[4])
  PCL_ADD_RGB;
  union {
    struct {
      float confidence_ratio;
    };
    float data_c[4];
  };
  PCL_MAKE_ALIGNED_OPERATOR_NEW
} EIGEN_ALIGN16;  // enforce SSE padding for correct memory alignment

struct PointXYZRGBConfidenceRatio : public _PointXYZRGBConfidenceRatio {
  inline PointXYZRGBConfidenceRatio(const _PointXYZRGBConfidenceRatio& p) {
    // XZY
    x = p.x;
    y = p.y;
    z = p.z;
    data[3] = 1.0f;

    // RGB
    rgba = p.rgba;

    // Confidence
    confidence_ratio = p.confidence_ratio;
  }

  inline PointXYZRGBConfidenceRatio(float _confidence_ratio = 1.f)
      : PointXYZRGBConfidenceRatio(0.f, 0.f, 0.f, 0, 0, 0, _confidence_ratio) {}

  inline PointXYZRGBConfidenceRatio(std::uint8_t _r, std::uint8_t _g, std::uint8_t _b)
      : PointXYZRGBConfidenceRatio(0.f, 0.f, 0.f, _r, _g, _b) {}

  inline PointXYZRGBConfidenceRatio(float _x, float _y, float _z) : PointXYZRGBConfidenceRatio(_x, _y, _z, 0, 0, 0) {}

  inline PointXYZRGBConfidenceRatio(float _x, float _y, float _z, std::uint8_t _r, std::uint8_t _g, std::uint8_t _b,
                                    float _confidence_ratio = 1.f) {
    x = _x;
    y = _y;
    z = _z;
    data[3] = 1.0f;

    r = _r;
    g = _g;
    b = _b;
    a = 255;

    confidence_ratio = _confidence_ratio;
  }

  friend std::ostream& operator<<(std::ostream& os, const PointXYZRGBConfidenceRatio& p);
};

PCL_EXPORTS std::ostream& operator<<(std::ostream& os, const PointXYZRGBConfidenceRatio& p);

}  // namespace pcl

namespace elevation_mapping {
using PointCloudType = pcl::PointCloud<pcl::PointXYZRGBConfidenceRatio>;
}  // namespace elevation_mapping

POINT_CLOUD_REGISTER_POINT_STRUCT(pcl::_PointXYZRGBConfidenceRatio,             // here we assume a XYZ + "confidence_ratio" (as fields)
                                  (float, x, x)                                 // NOLINT
                                  (float, y, y)                                 // NOLINT
                                  (float, z, z)                                 // NOLINT
                                  (std::uint32_t, rgba, rgba)                   // NOLINT
                                  (float, confidence_ratio, confidence_ratio))  // NOLINT

POINT_CLOUD_REGISTER_POINT_WRAPPER(pcl::PointXYZRGBConfidenceRatio, pcl::_PointXYZRGBConfidenceRatio)