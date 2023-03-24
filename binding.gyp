{
  "variables": {
    "openssl_fips" : "0"
  },
  "targets": [
    {
      "target_name": "iselevated",
      "sources": [
        "src/iselevated.cc"
      ],
      "msvs_configuration_attributes": {
        "SpectreMitigation": "Spectre"
      },
      "msvs_settings": {
        "VCCLCompilerTool": {
          "AdditionalOptions": [
            "/guard:cf",
            "/we4244",
            "/we4267",
            "/ZH:SHA_256"
          ]
        },
        "VCLinkerTool": {
          "AdditionalOptions": [
            "/guard:cf"
          ]
        }
      }
    }
  ]
}
