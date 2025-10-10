#include <iostream>
#include <chrono>
#include <curl/curl.h>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    return size * nmemb; // Discard the data (we only care about speed)
}

int main() {
    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        // Test URL (choose a file that exists online, e.g., a speed test file)
        curl_easy_setopt(curl, CURLOPT_URL, "http://ipv4.download.thinkbroadband.com/10MB.zip");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

        // Start time
        auto start = std::chrono::high_resolution_clock::now();

        res = curl_easy_perform(curl);

        if (res == CURLE_OK) {
            double bytes;
            curl_easy_getinfo(curl, CURLINFO_SIZE_DOWNLOAD, &bytes);

            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;

            double speed_bps = bytes / elapsed.count();        // Bytes per second
            double speed_kbps = speed_bps / 1024.0;            // KB/s
            double speed_mbps = (speed_bps * 8) / (1024 * 1024); // Mbps

            std::cout << "Downloaded: " << bytes / (1024 * 1024) << " MB\n";
            std::cout << "Time: " << elapsed.count() << " seconds\n";
            std::cout << "Speed: " << speed_kbps << " KB/s (" << speed_mbps << " Mbps)\n";
        } else {
            std::cerr << "Download failed: " << curl_easy_strerror(res) << "\n";
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return 0;
}
