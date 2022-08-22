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

#include <gtest/gtest.h>
#include "EnergyPlusFixture.hpp"

#include "../ForwardTranslator.hpp"
#include "../ReverseTranslator.hpp"

#include "../../model/Model.hpp"
#include "../../model/OutputControlReportingTolerances.hpp"
#include "../../model/OutputControlReportingTolerances_Impl.hpp"

#include "../../utilities/idf/IdfFile.hpp"
#include "../../utilities/idf/Workspace.hpp"
#include "../../utilities/idf/IdfObject.hpp"
#include "../../utilities/idf/WorkspaceObject.hpp"

#include <utilities/idd/OutputControl_ReportingTolerances_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

using namespace openstudio::energyplus;
using namespace openstudio::model;
using namespace openstudio;

TEST_F(EnergyPlusFixture, ForwardTranslator_OutputControlReportingTolerances) {

  // Not there, and workspace should not have it
  {
    Model m;
    ForwardTranslator ft;
    Workspace w = ft.translateModel(m);

    WorkspaceObjectVector idfObjs = w.getObjectsByType(IddObjectType::OutputControl_ReportingTolerances);
    ASSERT_EQ(0u, idfObjs.size());
  }

  // It's there
  {
    Model m;
    ForwardTranslator ft;

    OutputControlReportingTolerances outputControlReportingTolerances = m.getUniqueModelObject<OutputControlReportingTolerances>();

    EXPECT_TRUE(outputControlReportingTolerances.setToleranceforTimeHeatingSetpointNotMet(1.16));
    EXPECT_TRUE(outputControlReportingTolerances.setToleranceforTimeCoolingSetpointNotMet(0.75));

    Workspace w = ft.translateModel(m);

    WorkspaceObjectVector idfObjs = w.getObjectsByType(IddObjectType::OutputControl_ReportingTolerances);
    ASSERT_EQ(1u, idfObjs.size());

    WorkspaceObject idf_reportingtolerances(idfObjs[0]);

    EXPECT_EQ(1.16, idf_reportingtolerances.getDouble(OutputControl_ReportingTolerancesFields::ToleranceforTimeHeatingSetpointNotMet, false).get());
    EXPECT_EQ(0.75, idf_reportingtolerances.getDouble(OutputControl_ReportingTolerancesFields::ToleranceforTimeCoolingSetpointNotMet, false).get());
  }
}

TEST_F(EnergyPlusFixture, ReverseTranslator_OutputControlReportingTolerances) {

  ReverseTranslator rt;

  Workspace w(StrictnessLevel::Minimal, IddFileType::EnergyPlus);

  // Not there, Model shouldn't have it either
  Model m;
  m = rt.translateWorkspace(w);
  EXPECT_FALSE(m.getOptionalUniqueModelObject<OutputControlReportingTolerances>());

  OptionalWorkspaceObject _i_outputControlReportingTolerances = w.addObject(IdfObject(IddObjectType::OutputControl_ReportingTolerances));
  ASSERT_TRUE(_i_outputControlReportingTolerances);

  EXPECT_TRUE(_i_outputControlReportingTolerances->setDouble(OutputControl_ReportingTolerancesFields::ToleranceforTimeHeatingSetpointNotMet, 1.75));
  EXPECT_TRUE(_i_outputControlReportingTolerances->setDouble(OutputControl_ReportingTolerancesFields::ToleranceforTimeCoolingSetpointNotMet, 0.25));

  m = rt.translateWorkspace(w);

  // Get the unique object
  OutputControlReportingTolerances outputControlReportingTolerances = m.getUniqueModelObject<OutputControlReportingTolerances>();
  EXPECT_EQ(1.75, outputControlReportingTolerances.toleranceforTimeHeatingSetpointNotMet());
  EXPECT_EQ(0.25, outputControlReportingTolerances.toleranceforTimeCoolingSetpointNotMet());
}