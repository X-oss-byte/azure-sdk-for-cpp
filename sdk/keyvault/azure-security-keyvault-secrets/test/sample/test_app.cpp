// Copyright (c) Microsoft Corporation. All rights reserved.
// SPDX-License-Identifier: MIT
#if defined(_MSC_VER)
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <azure/identity.hpp>

#include <azure/keyvault/keyvault_secrets.hpp>

using namespace Azure::Security::KeyVault::Secrets;

int main()
{
  auto tenantId = std::getenv("AZURE_TENANT_ID");
  auto clientId = std::getenv("AZURE_CLIENT_ID");
  auto clientSecret = std::getenv("AZURE_CLIENT_SECRET");
  auto credential
      = std::make_shared<Azure::Identity::ClientSecretCredential>(tenantId, clientId, clientSecret);

  SecretClient secretClient(std::getenv("AZURE_KEYVAULT_URL"), credential);
  // just a response, with a secret
  auto response = secretClient.GetSecret("testSecret");

  // just a response, with a secret
  auto response2 = secretClient.GetDeletedSecret("someSecret");
  return 0;
}
