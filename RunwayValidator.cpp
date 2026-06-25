#include "RunwayValidator.h"
#include "RunwayValidatorVisitor.h"

void RunwayValidator::validate(const Plane* plane, const Runway* runway)
{
    RunwayValidatorVisitor visitor(*runway);
    plane->acceptValidator(visitor);
}
