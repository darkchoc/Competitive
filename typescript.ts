export class FlightFunctions {
    @Function()
    public currentFlightDestinations(airportCode: string): Set<string> {
        const flightsFromAirport = Objects.search().flights().filter(flight => flight.departureAirport.exactMatch(airportCode)).all();
        const destinations = flightsFromAirport.map(flight => flight.arrivalAiportCode!)
        return new Set(destinations);
    }

    public async getAllObjects(flightSet: ObjectSet<Flight>, airportSet: ObjectSet<Airport>): FunctionsMap<Flight, string | undefined) {
        const map = new FunctionsMap<Flight, string>();
        const [flights, airports] = await Promise.all([flightSet.allAsync(), airportSet.allAsync()]);

        // Modifying linked objects
        object.oneToOneProperty.set(newValue);
        object.oneToOneProperty.clear();
        object.oneToManyProperty.add(newValue);
        object.oneToManyProperty.remove(newValue);

        // Setting value for array property
        let arrayPropertyCopy = [...object.arrayProperty];
        arrayPropertyCopy.push(newVal);
        object.arrayProperty = arrayPropertyCopy;

        // Setting value for normal property
        object.normalProperty = newValue;

        // Creating new object
        let newObject = Object().create().flight(flightId);
        // Deleting object
        newObject.delete()

        // aggregation
        let maxDuration = await Objects.search().flights().max(flight => flight.duration);
        let countOfFlights = await Objects.search().flights().count();
        
    }
}