#include "utility/exporter.hpp"

#include "statistical/distribution_uniform.hpp"
#include "evt/gev_distribution.hpp"
#include "evt/gpd_distribution.hpp"
#include "global.hpp"

#include <iostream>

namespace chronovise {

    template<typename T_INPUT, typename T_TIME>
    std::unique_ptr<std::ofstream> Exporter<T_INPUT,T_TIME>::open_stream(const std::string& filename) {

        std::unique_ptr<std::ofstream> file  = std::make_unique<std::ofstream>();

        // Throw exception if opening file is a failure
        file->exceptions(std::ofstream::failbit | std::ofstream::badbit);

        // Trying to open it
        file->open(filename);

        return std::move(file);
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

    template<typename T_INPUT, typename T_TIME>
    void Exporter<T_INPUT,T_TIME>::save_wcots(const std::string& filename) const {
        auto file = open_stream(filename);
        *file << "INPUT,WCOT" << std::endl;

        const auto &measures = aec.get_wcots();
        for (const auto &m : measures) {
            *file << m.first << ',' << m.second << std::endl;
        }
    }

    template<typename T_INPUT, typename T_TIME>
    void Exporter<T_INPUT,T_TIME>::save_estimated_distributions(const std::string& filename) const {
        auto file = open_stream(filename);
        *file << "TYPE,LOCATION,SCALE,SHAPE" << std::endl;

        const auto &distributions = aec.get_estimated_distributions();
        for (const auto d : distributions) {

            switch (d->get_type()) {
                case distribution_t::EVT_GEV:
                {
                    auto new_d = std::dynamic_pointer_cast<GEV_Distribution>(d);
                    *file << "GEV," << new_d->get_location() << ',' << new_d->get_scale() << ','
                                    << new_d->get_shape() << std::endl;
                }
                break;
                case distribution_t::EVT_GPD:
                {
                    auto new_d = std::dynamic_pointer_cast<GPD_Distribution>(d);
                    *file << "GPD," << new_d->get_location() << ',' << new_d->get_scale() << ','
                                    << new_d->get_shape() << std::endl;
                }
                break;
                case distribution_t::UNIFORM:
                {
                    auto new_d   = std::dynamic_pointer_cast<DistributionUniform>(d);
                    auto ab_pair = new_d->get_parameters();
                    *file << "UNI," << (ab_pair.first + ab_pair.second)/2 << ','
                                    << (ab_pair.second - ab_pair.first)/2 << ','
                                    << '0' << std::endl;
                }
                break;
                case distribution_t::UNKNOWN:
                default:
                    *file << "UNK,0,0,0" << std::endl;
                break;
            }

        }
    }


TEMPLATE_CLASS_IMPLEMENTATION(Exporter);

} // namespace chronovise

