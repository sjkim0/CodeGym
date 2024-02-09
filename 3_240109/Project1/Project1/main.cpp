#include <iostream>
#include <vector>
#include <numeric>  // Include the header for std::accumulate

const double PI = 3.14159265358979323846;

// Function to demodulate an FM-modulated signal
std::string fm_demodulate(const std::vector<double>& modulated_signal, double sample_rate, double frequency_deviation, double carrier_frequency) {
    std::vector<double> demodulated_signal;

    for (size_t i = 1; i < modulated_signal.size(); ++i) {
        // Integrate the phase to demodulate the signal
        double phase_increment = 2.0 * PI * carrier_frequency / sample_rate +
            frequency_deviation * modulated_signal[i];

        // Accumulate the values in the modulated_signal vector up to the current index
        double integrated_phase = std::accumulate(modulated_signal.begin(), modulated_signal.begin() + i, 0.0,
            [=](double sum, double value) {
                return sum + phase_increment;
            });

        // Normalize the phase to keep it within the range [0, 2*pi]
        while (integrated_phase >= 2 * PI) {
            integrated_phase -= 2 * PI;
        }

        demodulated_signal.push_back(integrated_phase);
    }

    // Recover ASCII values from demodulated signal
    std::string recovered_message;
    for (size_t i = 0; i < demodulated_signal.size(); i += static_cast<size_t>(sample_rate)) {
        int ascii_value = static_cast<int>(demodulated_signal[i] / frequency_deviation);
        recovered_message.push_back(static_cast<char>(ascii_value));
    }

    return recovered_message;
}

int main() {
    // Example parameters
    double sample_rate = 10000.0;  // Hz
    double frequency_deviation = 5000.0;  // Hz
    double carrier_frequency = 100000.0;  // Hz
    std::string message = "Hello, World!";

    // ... (FM Modulation code not shown for brevity)

    // FM Demodulation
    std::string recovered_message = fm_demodulate(modulated_signal, sample_rate, frequency_deviation, carrier_frequency);

    // Output the recovered message
    std::cout << "Recovered Message: " << recovered_message << std::endl;

    return 0;
}