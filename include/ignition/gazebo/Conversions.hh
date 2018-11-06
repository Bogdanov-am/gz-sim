/*
 * Copyright (C) 2018 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/
#ifndef IGNITION_GAZEBO_CONVERSIONS_HH_
#define IGNITION_GAZEBO_CONVERSIONS_HH_

#include <ignition/msgs/boxgeom.pb.h>
#include <ignition/msgs/cylindergeom.pb.h>
#include <ignition/msgs/geometry.pb.h>
#include <ignition/msgs/light.pb.h>
#include <ignition/msgs/material.pb.h>
#include <ignition/msgs/planegeom.pb.h>
#include <ignition/msgs/spheregeom.pb.h>

#include <ignition/common/Console.hh>
#include <sdf/Box.hh>
#include <sdf/Cylinder.hh>
#include <sdf/Geometry.hh>
#include <sdf/Light.hh>
#include <sdf/Material.hh>
#include <sdf/Plane.hh>
#include <sdf/Sphere.hh>

namespace ignition
{
  namespace gazebo
  {
    // Inline bracket to help doxygen filtering.
    inline namespace IGNITION_GAZEBO_VERSION_NAMESPACE {
    /// \brief Generic conversion from an SDF geometry to another type.
    /// \param[in] _in SDF geometry.
    /// \return Conversion result.
    /// \tparam OUT Output type.
    template<class OUT>
    OUT Convert(const sdf::Geometry &_in)
    {
      OUT::ConversionNotImplemented;
    }

    /// \brief Specialized conversion from an SDF geometry to a geometry
    /// message.
    /// \param[in] _in SDF geometry.
    /// \return Geometry message.
    template<>
    msgs::Geometry Convert(const sdf::Geometry &_in)
    {
      msgs::Geometry out;
      if (_in.Type() == sdf::GeometryType::BOX && _in.BoxShape())
      {
        out.set_type(msgs::Geometry::BOX);
        msgs::Set(out.mutable_box()->mutable_size(), _in.BoxShape()->Size());
      }
      else if (_in.Type() == sdf::GeometryType::CYLINDER && _in.CylinderShape())
      {
        out.set_type(msgs::Geometry::CYLINDER);
        out.mutable_cylinder()->set_radius(_in.CylinderShape()->Radius());
        out.mutable_cylinder()->set_length(_in.CylinderShape()->Length());
      }
      else if (_in.Type() == sdf::GeometryType::PLANE && _in.PlaneShape())
      {
        out.set_type(msgs::Geometry::PLANE);
        msgs::Set(out.mutable_plane()->mutable_normal(),
                  _in.PlaneShape()->Normal());
        msgs::Set(out.mutable_plane()->mutable_size(),
                  _in.PlaneShape()->Size());
      }
      else if (_in.Type() == sdf::GeometryType::SPHERE && _in.SphereShape())
      {
        out.set_type(msgs::Geometry::SPHERE);
        out.mutable_sphere()->set_radius(_in.SphereShape()->Radius());
      }
      else
      {
        ignerr << "Geometry type [" << static_cast<int>(_in.Type())
               << "] not supported" << std::endl;
      }
      return out;
    }

    /// \brief Generic conversion from an SDF material to another type.
    /// \param[in] _in SDF material.
    /// \return Conversion result.
    /// \tparam OUT Output type.
    template<class OUT>
    OUT Convert(const sdf::Material &_in)
    {
      OUT::ConversionNotImplemented;
    }

    /// \brief Specialized conversion from an SDF material to a material
    /// message.
    /// \param[in] _in SDF material.
    /// \return Material message.
    template<>
    msgs::Material Convert(const sdf::Material &_in)
    {
      msgs::Material out;
      msgs::Set(out.mutable_ambient(), _in.Ambient());
      msgs::Set(out.mutable_diffuse(), _in.Diffuse());
      msgs::Set(out.mutable_specular(), _in.Specular());
      return out;
    }

    /// \brief Generic conversion from an SDF light to another type.
    /// \param[in] _in SDF light.
    /// \return Conversion result.
    /// \tparam OUT Output type.
    template<class OUT>
    OUT Convert(const sdf::Light &_in)
    {
      OUT::ConversionNotImplemented;
    }

    /// \brief Specialized conversion from an SDF light to a light
    /// message.
    /// \param[in] _in SDF light.
    /// \return Light message.
    template<>
    msgs::Light Convert(const sdf::Light &_in)
    {
      msgs::Light out;
      out.set_name(_in.Name());
      msgs::Set(out.mutable_pose(), _in.Pose());
      msgs::Set(out.mutable_diffuse(), _in.Diffuse());
      msgs::Set(out.mutable_specular(), _in.Specular());
      out.set_attenuation_constant(_in.ConstantAttenuationFactor());
      out.set_attenuation_linear(_in.LinearAttenuationFactor());
      out.set_attenuation_quadratic(_in.QuadraticAttenuationFactor());
      out.set_range(_in.AttenuationRange());
      msgs::Set(out.mutable_direction(), _in.Direction());
      out.set_cast_shadows(_in.CastShadows());
      out.set_spot_inner_angle(_in.SpotInnerAngle().Radian());
      out.set_spot_outer_angle(_in.SpotOuterAngle().Radian());
      out.set_spot_falloff(_in.SpotFalloff());
      if (_in.Type() == sdf::LightType::POINT)
        out.set_type(msgs::Light_LightType_POINT);
      else if (_in.Type() == sdf::LightType::SPOT)
        out.set_type(msgs::Light_LightType_SPOT);
      else if (_in.Type() == sdf::LightType::DIRECTIONAL)
        out.set_type(msgs::Light_LightType_DIRECTIONAL);
      return out;
    }
    }
  }
}
#endif