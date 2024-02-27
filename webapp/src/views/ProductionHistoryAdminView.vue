<template>
  <BasePage :title="$t('menu.ProductionHistory')" :isLoading="dataLoading">
    <BootstrapAlert v-model="showAlert" dismissible :variant="alertType">
      {{ alertMessage }}
    </BootstrapAlert>
    <form @submit="postHistoryUrl">
        <CardElement :text="$t('productionhistoryadmin.urlConfiguration')" textVariant="text-bg-primary">
          <InputElement placeholder="https://" :label="$t('productionhistoryadmin.fetchingUrl')" type="text" v-model="url"/>
        </CardElement>
        <FormFooter />
      </form>
    </BasePage>
</template>

<script lang="ts">
import { defineComponent } from 'vue';
import BasePage from '@/components/BasePage.vue';
import CardElement from '@/components/CardElement.vue';
import { authHeader, handleResponse } from '@/utils/authentication';
import FormFooter from '@/components/FormFooter.vue';
import InputElement from '@/components/InputElement.vue';
import BootstrapAlert from "@/components/BootstrapAlert.vue";

export default defineComponent({
    components: {
        BasePage,
        CardElement,
        FormFooter,
        InputElement,
        BootstrapAlert,
    },
    data() {
        return {
            dataLoading: false,
            url: "",

            alertMessage: "",
            alertType: "info",
            showAlert: false,
        };
    },
    created() {
        this.getHistoryUrl();
    },
    methods: {
        postHistoryUrl(e: Event) {
            e.preventDefault();

            const formData = new FormData();
            formData.append("data", JSON.stringify({ url: this.url }));

            fetch("/api/production-history/url", {
                method: "POST",
                headers: authHeader(),
                body: formData,
            }).then((response) => handleResponse(response, this.$emitter, this.$router))
              .then((data) => {
                  this.alertMessage = this.$t('apiresponse.' + data.code, data.param);
                  this.alertType = data.type;
                  this.showAlert = true;
              });
        },
        getHistoryUrl() {
            this.dataLoading = true;
            fetch("/api/production-history/url", { headers: authHeader() })
                .then((response) => handleResponse(response, this.$emitter, this.$router))
                .then((data) => {
                    this.url = data;
                })
                .finally(() => {
                  this.dataLoading = false;
                })
        },
    },
});
</script>