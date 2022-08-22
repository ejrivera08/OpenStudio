/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2022, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
*  following conditions are met:
*
*  (1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
*  disclaimer.
*
*  (2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
*  disclaimer in the documentation and/or other materials provided with the distribution.
*
*  (3) Neither the name of the copyright holder nor the names of any contributors may be used to endorse or promote products
*  derived from this software without specific prior written permission from the respective party.
*
*  (4) Other than as required in clauses (1) and (2), distributions in any form of modifications or other derivative works
*  may not use the "OpenStudio" trademark, "OS", "os", or any other confusingly similar designation without specific prior
*  written permission from Alliance for Sustainable Energy, LLC.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND ANY CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
*  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S), ANY CONTRIBUTORS, THE UNITED STATES GOVERNMENT, OR THE UNITED
*  STATES DEPARTMENT OF ENERGY, NOR ANY OF THEIR EMPLOYEES, BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
*  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
*  USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
*  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
*  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***********************************************************************************************************************/

#ifndef MODEL_MATERIALPROPERTYPHASECHANGE_HPP
#define MODEL_MATERIALPROPERTYPHASECHANGE_HPP

#include <vector>
#include "ModelAPI.hpp"
#include "ModelObject.hpp"

namespace openstudio {
namespace model {

  class Material;
  class StandardOpaqueMaterial;
  class MasslessOpaqueMaterial;

  namespace detail {

    class MaterialPropertyPhaseChange_Impl;

  }  // namespace detail

  /** This class implements a temperature enthalpy */
  class MODEL_API TemperatureEnthalpy
  {
   public:
    TemperatureEnthalpy(double temperature, double enthalpy);

    double temperature() const;
    double enthalpy() const;

   private:
    double m_temperature;
    double m_enthalpy;
    REGISTER_LOGGER("openstudio.model.TemperatureEnthalpy");
  };

  // Overload operator<<
  MODEL_API std::ostream& operator<<(std::ostream& out, const openstudio::model::TemperatureEnthalpy& temperatureEnthalpy);

  /** MaterialPropertyPhaseChange is a ModelObject that wraps the OpenStudio IDD object 'OS:MaterialProperty:PhaseChange'. */
  class MODEL_API MaterialPropertyPhaseChange : public ModelObject
  {
   public:
    /** @name Constructors and Destructors */
    //@{

    explicit MaterialPropertyPhaseChange(StandardOpaqueMaterial& material);

    explicit MaterialPropertyPhaseChange(MasslessOpaqueMaterial& material);

    explicit MaterialPropertyPhaseChange(StandardOpaqueMaterial& material, const std::vector<TemperatureEnthalpy>& temperatureEnthalpys);

    explicit MaterialPropertyPhaseChange(MasslessOpaqueMaterial& material, const std::vector<TemperatureEnthalpy>& temperatureEnthalpys);

    virtual ~MaterialPropertyPhaseChange() {}

    //@}

    static IddObjectType iddObjectType();

    /** @name Getters */
    //@{

    std::string materialName() const;

    Material material() const;

    double temperatureCoefficientforThermalConductivity() const;

    bool isTemperatureCoefficientforThermalConductivityDefaulted() const;

    std::vector<TemperatureEnthalpy> temperatureEnthalpys() const;

    unsigned int numberofTemperatureEnthalpys() const;

    //@}
    /** @name Setters */
    //@{

    bool setTemperatureCoefficientforThermalConductivity(double temperatureCoefficientforThermalConductivity);

    void resetTemperatureCoefficientforThermalConductivity();

    bool addTemperatureEnthalpy(const TemperatureEnthalpy& temperatureEnthalpy);

    bool addTemperatureEnthalpy(double temperature, double enthalpy);

    bool addTemperatureEnthalpys(const std::vector<TemperatureEnthalpy>& temperatureEnthalpys);

    void removeTemperatureEnthalpy(unsigned groupIndex);

    void removeAllTemperatureEnthalpys();

    //@}
    /** @name Other */
    //@{

    //@}
   protected:
    /// @cond
    typedef detail::MaterialPropertyPhaseChange_Impl ImplType;

    explicit MaterialPropertyPhaseChange(std::shared_ptr<detail::MaterialPropertyPhaseChange_Impl> impl);

    friend class detail::MaterialPropertyPhaseChange_Impl;
    friend class Model;
    friend class IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    /// @endcond
   private:
    REGISTER_LOGGER("openstudio.model.MaterialPropertyPhaseChange");
  };

  /** \relates MaterialPropertyPhaseChange*/
  typedef boost::optional<MaterialPropertyPhaseChange> OptionalMaterialPropertyPhaseChange;

  /** \relates MaterialPropertyPhaseChange*/
  typedef std::vector<MaterialPropertyPhaseChange> MaterialPropertyPhaseChangeVector;

}  // namespace model
}  // namespace openstudio

#endif  // MODEL_MATERIALPROPERTYPHASECHANGE_HPP