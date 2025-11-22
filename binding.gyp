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
      "cflags": [
        "-O2",
        "-D_FORTIFY_SOURCE=2",
      ],
      "msvs_configuration_attributes": {
        "SpectreMitigation": "Spectre"
      },
      "msvs_settings": {
        "VCCLCompilerTool": {
          "AdditionalOptions": [
            "/guard:cf",
            "/W3",
            "/we4244",
            "/we4267",
            "/ZH:SHA_256"
          ]
        },
        "VCLinkerTool": {
          "AdditionalOptions": [
            "/DYNAMICBASE",
            "/guard:cf"
          ]
        }
      }
    }
  ]
}
