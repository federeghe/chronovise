#include "utility/exporter.hpp"

#include "global.hpp"

namespace chronovise {

    template<typename T_INPUT, typename T_TIME>
    std::unique_ptr<std::ofstream> Exporter<T_INPUT,T_TIME>::open_stream(const std::string& filename) {

        std::unique_ptr<std::ofstream> file (new std::ofstream);

        // Launch outside exception if opening file is a failure
        file->exceptions(std::ofstream::failbit | std::ofstream::badbit);

        // Trying
        file->open(filename);

        return file;

    }

    template<typename T_INPUT, typename T_TIME>
    void Exporter<T_INPUT,T_TIME>::save_time_samples(const std::string& filename) const {

        auto file = open_stream(filename);

        *file << "INPUT,TIME" << std::endl;

        const auto &measures = aec.get_measures();

        for (const auto &m : measures) {
            *file << m.first << ',' << m.second << std::endl;
        }

    }

TEMPLATE_CLASS_IMPLEMENTATION(Exporter);

} // namespace chronovise

