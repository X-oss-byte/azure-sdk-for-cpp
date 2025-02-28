// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

/**
 * @file
 * @brief Workload Identity Credential and options.
 */

#pragma once

#include "azure/identity/detail/client_credential_core.hpp"
#include "azure/identity/detail/token_cache.hpp"

#include <azure/core/credentials/token_credential_options.hpp>

#include <string>
#include <vector>

namespace Azure { namespace Identity {
  namespace _detail {
    class TokenCredentialImpl;
  } // namespace _detail

  /**
   * @brief Options for workload identity credential.
   *
   */
  struct WorkloadIdentityCredentialOptions final : public Core::Credentials::TokenCredentialOptions
  {
    /**
     * @brief Authentication authority URL.
     * @note Default value is Azure AD global authority (https://login.microsoftonline.com/).
     *
     * @note Example of an authority host string: "https://login.microsoftonline.us/". See national
     * clouds' Azure AD authentication endpoints:
     * https://docs.microsoft.com/azure/active-directory/develop/authentication-national-cloud.
     */
    std::string AuthorityHost = _detail::ClientCredentialCore::AadGlobalAuthority;

    /**
     * @brief For multi-tenant applications, specifies additional tenants for which the credential
     * may acquire tokens. Add the wildcard value `"*"` to allow the credential to acquire tokens
     * for any tenant in which the application is installed.
     */
    std::vector<std::string> AdditionallyAllowedTenants;
  };

  /**
   * @brief Workload Identity Credential supports Azure workload identity authentication on
   * Kubernetes and other hosts supporting workload identity. See the Azure Kubernetes Service
   * documentation at https://learn.microsoft.com/azure/aks/workload-identity-overview for more
   * information.
   *
   */
  class WorkloadIdentityCredential final : public Core::Credentials::TokenCredential {
  private:
    _detail::TokenCache m_tokenCache;
    _detail::ClientCredentialCore m_clientCredentialCore;
    std::unique_ptr<_detail::TokenCredentialImpl> m_tokenCredentialImpl;
    std::string m_requestBody;
    std::string m_tokenFilePath;

    explicit WorkloadIdentityCredential(
        std::string tenantId,
        std::string const& clientId,
        std::string const& tokenFilePath,
        std::string const& authorityHost,
        std::vector<std::string> additionallyAllowedTenants,
        Core::Credentials::TokenCredentialOptions const& options);

  public:
    /**
     * @brief Constructs a Workload Identity Credential.
     *
     * @param tenantId Tenant ID.
     * @param clientId Client ID.
     * @param tokenFilePath Path of a file containing a Kubernetes service account token.
     * @param options Options for token retrieval.
     */
    explicit WorkloadIdentityCredential(
        std::string tenantId,
        std::string const& clientId,
        std::string const& tokenFilePath,
        Core::Credentials::TokenCredentialOptions const& options
        = Core::Credentials::TokenCredentialOptions());

    /**
     * @brief Constructs a Workload Identity Credential.
     *
     * @param tenantId Tenant ID.
     * @param clientId Client ID.
     * @param tokenFilePath Path of a file containing a Kubernetes service account token.
     * @param options Options for token retrieval.
     */
    explicit WorkloadIdentityCredential(
        std::string tenantId,
        std::string const& clientId,
        std::string const& tokenFilePath,
        WorkloadIdentityCredentialOptions const& options);

    /**
     * @brief Destructs `%WorkloadIdentityCredential`.
     *
     */
    ~WorkloadIdentityCredential() override;

    /**
     * @brief Gets an authentication token.
     *
     * @param tokenRequestContext A context to get the token in.
     * @param context A context to control the request lifetime.
     *
     * @throw Azure::Core::Credentials::AuthenticationException Authentication error occurred.
     */
    Core::Credentials::AccessToken GetToken(
        Core::Credentials::TokenRequestContext const& tokenRequestContext,
        Core::Context const& context) const override;
  };

}} // namespace Azure::Identity
