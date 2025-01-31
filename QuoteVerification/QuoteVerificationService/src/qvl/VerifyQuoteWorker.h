/*
 * Copyright (C) 2011-2021 Intel Corporation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Intel Corporation nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef QUOTEVERIFICATIONLIBRARYWRAPPER_VERIFYQUOTEQORKER_H
#define QUOTEVERIFICATIONLIBRARYWRAPPER_VERIFYQUOTEQORKER_H

#include <napi.h>
#include <SgxEcdsaAttestation/QuoteVerification.h>
#include "BaseWorker.h"
#include "VerifyQuoteErrorSource.h"

namespace intel::sgx::dcap::qvlwrapper {

    class VerifyQuoteWorker : public BaseWorker {
    public:
        VerifyQuoteWorker(Napi::Env &env, Napi::Promise::Deferred &promise, const std::string& requestId,
                          uint8_t *quote,
                          size_t quoteSize,
                          std::string pckCert,
                          std::string tcbInfo,
                          std::string qeIdentity,
                          std::string pckCertIssuerCertChain,
                          std::string tcbInfoIssuerCertChain,
                          std::string pckCrl,
                          std::string rootCaCrl,
                          std::string trustedRootCaPem,
                          std::string tcbInfoSigningChainTrustedRoot)
                : BaseWorker(env, promise, requestId),
                  quote(quote),
                  quoteSize(quoteSize),
                  pckCert(std::move(pckCert)),
                  tcbInfo(std::move(tcbInfo)),
                  qeIdentity(std::move(qeIdentity)),
                  pckCertIssuerCertChain(std::move(pckCertIssuerCertChain)),
                  tcbInfoIssuerCertChain(std::move(tcbInfoIssuerCertChain)),
                  pckCrl(std::move(pckCrl)),
                  rootCaCrl(std::move(rootCaCrl)),
                  trustedRootCaPem(std::move(trustedRootCaPem)),
                  tcbInfoSigningChainTrustedRoot(std::move(tcbInfoSigningChainTrustedRoot)) {}

        ~VerifyQuoteWorker() override = default;

        void Run() override;

        void OnOK() override;

        void OnError(const Napi::Error &e) override ;

    private:
        uint8_t *quote = nullptr;
        size_t quoteSize = 0;
        std::string pckCert;
        std::string tcbInfo;
        std::string qeIdentity;
        std::string pckCertIssuerCertChain;
        std::string tcbInfoIssuerCertChain;
        std::string pckCrl;
        std::string rootCaCrl;
        std::string trustedRootCaPem;
        std::string tcbInfoSigningChainTrustedRoot;

        Status qvlStatus = STATUS_OK;
        VerifyQuoteErrorSource errorSource;
    };

}
#endif //QUOTEVERIFICATIONLIBRARYWRAPPER_VERIFYQUOTEQORKER_H
